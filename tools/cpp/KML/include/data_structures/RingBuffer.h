/*!
 * @file RingBuffer.h
 * @brief Provides the declarations for the ring buffer data structure.
 */
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "IDataStructure.h"

namespace KML
{
    namespace DataStructures
    {
        /*!
         * @brief Streaming RingBuffer class declaration.
         */
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
                 * @copydoc IDataStructure::update()
                 */
                void update(const T& item) override;

                /*!
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

                /*!
                 * @brief Retrieve the last value in the RingBuffer.
                 */
                T pop();

                /*!
                 * @copydoc IDataStructure::full()
                 */
                bool full() const override;

                /*!
                 * @copydoc IDataStructure::empty()
                 */
                bool empty() const override;

                /*!
                 * @copydoc IDataStructure::size()
                 */
                size_t size() const override;

                /*!
                 * @copydoc IDataStructure::reset()
                 */
                void reset() override;

            private:
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
    }  // namespace DataStructures
}  // namespace KML

#include "RingBuffer.tcc"

#endif  // __RING_BUFFER_H__
