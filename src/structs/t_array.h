#pragma once

template<typename T>
struct array_t {
	void* m_pClass;
    void* m_pMonitor;
    void* m_pBounds;
    int32_t m_iMaxLength;
    T m_pItems[0];
	
	int32_t getCapacity() const {
        if (!this) return 0;
        return m_iMaxLength;
    }
	
    T* getPointer() {
        if (!this) return nullptr;
        return m_pItems;
    }
	
    std::vector<T> toVector() {
        if (!this) return {};
        std::vector<T> ret;
        for (int i = 0; i < m_iMaxLength; i++)
            ret.push_back(m_pItems[i]);
        return std::move(ret);
    }
	
    bool copyFrom(const std::vector<T> &vec) {
        if (!this) return false;
        return copyFrom((T*)vec.data(), (int)vec.size());
    }
	
    bool copyFrom(T* arr, int size) {
        if (!this) return false;
        if (size > m_iMaxLength) return false;
        memcpy(m_pItems, arr, size * sizeof(T));
        return true;
    }
	
    void copyTo(T* arr) {
        if (!this || !isAllocated(m_pItems)) return;
        memcpy(arr, m_pItems, sizeof(T) * m_iMaxLength);
    }
    
    T& operator[](int index) {
        if (getCapacity() <= index) {
            static T dummy;
            return dummy;
        }
        return m_pItems[index];
    }
	
    T at(int index) {
        if (!this || getCapacity() <= index || empty()) return T();
        return m_pItems[index];
    }
	
    bool empty() {
        if (!this) return true;
        return getCapacity() <= 0;
    }
	
    static array_t<T>* Create(int capacity) {
        auto arr = (array_t<T>*)malloc(sizeof(array_t<T>) + sizeof(T) * capacity);
        arr->m_iMaxLength = capacity;
        return arr;
    }
    
    static array_t<T>* Create(const std::vector<T>& vec) {
        return Create(vec.data(), vec.size());
    }
    
    static array_t<T>* Create(T* arr, int size) {
        array_t<T>* newArr = Create(size);
        newArr->copyFrom(arr, size);
        return newArr;
    }
    
    int32_t length() const {
        return getCapacity();
    }
    
    T* data() {
        return getPointer();
    }
};
