/*!
 * @file RingBuffer.h
 * @brief Provides the declarations for the ring buffer data structure.
 */
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <cstdint>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>

#include "IDataStructure.h"

namespace KML
{
    namespace DataStructures
    {
        template<typename T = double>
        class RingBuffer : public IDataStructure<T>
        {
            // Create alias for type of data container.
            using Data = std::unique_ptr<T[], std::function<void(T*)>>;

            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The desired size of the ring buffer.
                 */
                explicit RingBuffer(const size_t& windowSize);

                /*!
                 * @brief Default Destructor.
                 */
                virtual ~RingBuffer() = delete;

                /*!
                 * @copydoc IDataStructure::update()
                 */
                virtual void update(const T& item) override;

                /*!
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

                /*!
                 * @brief Retrieve the head value of the RingBuffer..
                 */
                T pop();

                /*!
                 * @copydoc IDataStructure::full()
                 */
                virtual bool full() const override;

                /*!
                 * @copydoc IDataStructure::empty()
                 */
                virtual bool empty() const override;

                /*!
                 * @copydoc IDataStructure::size()
                 */
                virtual size_t size() const override;

                /*!
                 * @copydoc IDataStructure::reset()
                 */
                virtual void reset() override;

            protected:
                /*!
                 * @brief Underlying data structure to maintain.
                 */
                Data m_buffer;

                /*!
                 * @brief Lock used to lock operations. This allows for threading the 
                 *        ring buffer.
                 */
                std::mutex m_mutex;

                /*!
                 * @brief Current head index of the ring buffer.
                 */
                size_t m_head = 0;

                /*!
                 * @brief Current tail index of the ring buffer.
                 */
                size_t m_tail = 0;

                /*!
                 * @brief Whether the ring buffer is currently full. This is determined
                 *        by the input size windowSize.
                 */
                bool m_full = false;
        };
    } // DataStructures
} // KML

#include "RingBuffer.tcc"

#endif // __RING_BUFFER_H__
