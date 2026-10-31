bool esp_enabled = false;
ImColor esp_box_color_enemy = ImColor(255, 80,  80,  255); 
ImColor esp_box_color_team  = ImColor(80,  255, 80,  255);

ImDrawList* g_Draw = nullptr;

static bool ReadString16(uint64_t strObj, char* out, int maxLen) {
    if (!strObj) return false;
    int len = rpm<int>(strObj + 0x10);
    if (len <= 0 || len >= maxLen) return false;
    for (int i = 0; i < len; i++)
        out[i] = (char)rpm<uint16_t>(strObj + 0x14 + i * 2);
    out[len] = 0;
    return true;
}

static int DictSize(uint64_t dict) {
    if (!dict) return 0;
    return rpm<int>(dict + 0x20);
}
static uint64_t DictEntries(uint64_t dict) {
    return rpm<uint64_t>(dict + 0x10); 
}
static uint64_t DictValue(uint64_t entries, int i) {
    return rpm<uint64_t>(entries + 0x10 + 0x18 * i + 0x10);
}
static int DictHash(uint64_t entries, int i) {
    return rpm<int>(entries + 0x10 + 0x18 * i + 0x0);
}

static int ListSize(uint64_t list) {
    if (!list) return 0;
    return rpm<int>(list + 0x18);
}
static uint64_t ListItems(uint64_t list) {
    return rpm<uint64_t>(list + 0x10); 
}
static uint64_t ListGet(uint64_t list, int i) {
    uint64_t arr = ListItems(list);
    if (!arr) return 0;
    return rpm<uint64_t>(arr + 0x20 + 0x8 * i);
}

void DrawBox(const ImRect& r, ImColor col) {
    ImColor black(0, 0, 0, 220);
    g_Draw->AddRect(r.Min, r.Max, black, 0, 0, 2.8f);
    g_Draw->AddRect(r.Min, r.Max, col,   0, 0, 1.6f);
}

void player() {
    g_Draw = ImGui::GetBackgroundDrawList();
    if (!esp_enabled) return;

    uint64_t gyd_typeinfo = rpm<uint64_t>(il2cpp_base + 0x5152FD88);
    if (!gyd_typeinfo) return;
    uint64_t gyd_static   = rpm<uint64_t>(gyd_typeinfo + 0xB8);
    if (!gyd_static) return;
    uint64_t gyd          = rpm<uint64_t>(gyd_static + 0x0);
    if (!gyd) return;
    uint64_t localBfy  = rpm<uint64_t>(gyd + 0x68);
    if (!localBfy) return;
    uint8_t  localActor = rpm<uint8_t>(localBfy + 0x3C);
    int      localTeam  = rpm<int>(localBfy + 0x40);

    uint64_t ggk_typeinfo = rpm<uint64_t>(il2cpp_base + 0x5152F9B0); 
    if (!ggk_typeinfo) return;
    uint64_t ggk_static   = rpm<uint64_t>(ggk_typeinfo + 0xB8);
    if (!ggk_static) return;
    uint64_t ggk          = rpm<uint64_t>(ggk_static + 0x0);
    if (!ggk) return;

    uint64_t ylk = rpm<uint64_t>(ggk + 0x30);
    if (!ylk) return;
    uint64_t wuu      = rpm<uint64_t>(ylk + 0x10);
    if (!wuu) return;
    uint64_t wuu_arr  = rpm<uint64_t>(wuu + 0x10);
    int      wuu_cap  = rpm<int>(wuu + 0x18);
    int      wuu_head = rpm<int>(wuu + 0x1C);
    if (!wuu_arr || wuu_cap <= 0) return;

    int wip_idx      = (wuu_head - 1 + wuu_cap) % wuu_cap;
    uint64_t wip     = rpm<uint64_t>(wuu_arr + 0x20 + 0x8 * wip_idx);
    if (!wip) return;

    uint64_t ftaa    = rpm<uint64_t>(wip + 0x30);
    if (!ftaa) return;
    int      qqkCount = ListSize(ftaa);
    if (qqkCount <= 0 || qqkCount > 64) return;

    uint64_t lsnk      = rpm<uint64_t>(gyd + 0x60);
    uint64_t lsnkEntries = DictEntries(lsnk);
    int      lsnkCount   = DictSize(lsnk);

    for (int i = 0; i < qqkCount; i++) {
        uint64_t qqk = ListGet(ftaa, i);
        if (!qqk) continue;

        uint64_t trimCtx = qqk + 0x28; 
        uint8_t  actorId = rpm<uint8_t>(trimCtx + 0x0);

        if (actorId == localActor) continue;

        int  playerTeam = -1;
        bool isAlive    = false;

        if (lsnkEntries && lsnkCount > 0) {
            for (int j = 0; j < lsnkCount + 8; j++) { 
                if (DictHash(lsnkEntries, j) < 0) continue;
                uint64_t bfy = DictValue(lsnkEntries, j);
                if (!bfy) continue;
                uint8_t bActorId = rpm<uint8_t>(bfy + 0x3C);
                if (bActorId == actorId) {
                    playerTeam = rpm<int>(bfy + 0x40);
                    break;
                }
            }
        }

        if (playerTeam < 0) continue;      
        if (playerTeam == localTeam) continue; 

        uint64_t kpvx      = rpm<uint64_t>(qqk + 0x20);
        int      compCount  = ListSize(kpvx);
        if (compCount <= 0 || compCount > 32) continue;

        vec3_t   position  = {};
        bool     gotPos    = false;

        for (int c = 0; c < compCount; c++) {
            uint64_t comp = ListGet(kpvx, c);
            if (!comp) continue;

            uint64_t vtable = rpm<uint64_t>(comp);

            vec3_t candidate = rpm<vec3_t>(comp + 0x10);
            if (!gotPos &&
                candidate.x != 0.0f && candidate.y != 0.0f &&
                fabsf(candidate.x) < 8192.0f &&
                fabsf(candidate.y) < 512.0f  &&
                fabsf(candidate.z) < 8192.0f) {
                position = candidate;
                gotPos   = true;
            }

            bool cAlive = (rpm<uint8_t>(comp + 0x10) == 1);
            if (cAlive) isAlive = true;
        }

        if (!gotPos || !isAlive) continue;

        auto WorldToScreen = [&mat](vec3_t pos) -> vec3_t {
            float screenX = (mat.m11 * pos.x) + (mat.m21 * pos.y) + (mat.m31 * pos.z) + mat.m41;
            float screenY = (mat.m12 * pos.x) + (mat.m22 * pos.y) + (mat.m32 * pos.z) + mat.m42;
            float screenW = (mat.m14 * pos.x) + (mat.m24 * pos.y) + (mat.m34 * pos.z) + mat.m44;
            vec3_t r;
            if (screenW < 0.0001f) { r.z = -1; return r; }
            float cx = abs_ScreenX / 2.0f;
            float cy = abs_ScreenY / 2.0f;
            r.x = cx + (cx * screenX / screenW);
            r.y = cy - (cy * screenY / screenW);
            r.z = screenW;
            return r;
        };

        vec3_t w2sTop    = WorldToScreen(vec3_t(position.x, position.y + 1.67f, position.z));
        vec3_t w2sBottom = WorldToScreen(position);
        if (w2sTop.z <= 0 || w2sBottom.z <= 0) continue;

        float xLeft  = fminf(w2sTop.x, w2sBottom.x);
        float xRight = fmaxf(w2sTop.x, w2sBottom.x);
        float boxW   = fabsf(w2sTop.y - w2sBottom.y) / 4.0f;

        ImRect r(
            ImVec2(xLeft  - boxW, w2sTop.y),
            ImVec2(xRight + boxW, w2sBottom.y)
        );

        DrawBox(r, esp_box_color_enemy);
    }
}
