#pragma once

template <typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        return *m_Instance;
    }

    template<typename... Args>
    static void Create(Args&&... args)
    {
        if (!m_Instance)
            m_Instance = new T(std::forward<Args>(args)...);
    }

    static void Destroy()
    {
        if (m_Instance)
        {
            delete m_Instance;
            m_Instance = nullptr;
        }
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static T* m_Instance;
};

template <typename T>
T* Singleton<T>::m_Instance = nullptr;