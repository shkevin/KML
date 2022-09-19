/*!
 * @file  Bin.tcc
 * @brief Contains the templated implementation for the abstract Bin class.
 */
namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        IBin<T>::IBin(T left, T right, size_t count) : m_left(left),
            m_right(right), m_count(count)
        {
            // Do nothing.
        }

        template<typename T>
        IBin<T>::~IBin()
        {
            // Do nothing.
        }

        template<typename T>
        IBin<T>::IBin(const IBin& other)
        {
            this->m_left = other.m_left;
            this->m_right = other.m_right;
            this->m_count = other.m_count;
        }

        template<typename T>
        IBin<T>& IBin<T>::operator=(const IBin& rhs)
        {
            if(this != &rhs)
            {
                this->m_left = rhs.m_left;
                this->m_right = rhs.m_right;
                this->m_count = rhs.m_count;
            }

            return *this;
        }

        template<typename T>
        IBin<T>::IBin(IBin&& other)
        {
            this->m_left = other.m_left;
            this->m_right = other.m_right;
            this->m_count = other.m_count;
        }

        template<typename T>
        IBin<T>& IBin<T>::operator=(IBin&& rhs)
        {
            if(this != &rhs)
            {
                this->m_left = rhs.m_left;
                this->m_right = rhs.m_right;
                this->m_count = rhs.m_count;
            }

            return *this;
        }

        template<typename T>
        IBin<T> IBin<T>::operator+(const IBin& rhs) const
        {
            IBin l_bin = *this;
            if(rhs.m_left < l_bin.m_left) l_bin.m_left = rhs.m_left;
            if(rhs.m_right > l_bin.m_right) l_bin.m_right = rhs.m_right;
            l_bin.m_count += rhs.m_count;

            return l_bin;
        }

        template<typename T>
        IBin<T> IBin<T>::operator+=(const IBin<T>& other)
        {
            *this = *this + other;
            return *this;
        }

        template<typename T>
        bool IBin<T>::operator<(const IBin& rhs) const
        {
            return this->m_left < rhs.m_left;
        }

        template<typename T>
        bool IBin<T>::operator==(const IBin& rhs) const
        {
            return this->m_left == rhs.m_left && this->m_right == rhs.m_right;
        }

        template<typename T>
        std::ostream& operator<<(std::ostream& os, const IBin<T>& bin)
        {
             os << "[" << bin.m_left << ", " << bin.m_right << "] -> " << bin.m_count;
             return os;
        }

        template<typename T>
        size_t IBin<T>::getCount() const
        {
            return this->m_count;
        }
    } // DataStructures
} // KML
