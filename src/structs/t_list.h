#pragma once

template<typename T>
struct list_t {
    void* m_pClass;
    void* m_pUnk;
    array_t<T>* m_pItems;
    int32_t m_iSize;
    int32_t m_iVersion;
	
	std::vector<T> toVector() {
		std::vector<T> ret;
		for (int i = 0; i < m_iSize; i++) {
			ret.push_back(m_pItems->data()[i]);
		}
		return std::move(ret);
	}
    
    T* items() {
        return m_pItems->data();
    }
    
    int32_t size() const {
        return m_iSize;
    }
	
    T& operator[](int32_t index) {
        return (*m_pItems)[index];
    }
    
    const T& operator[](int32_t index) const {
        return (*m_pItems)[index];
    }
};
