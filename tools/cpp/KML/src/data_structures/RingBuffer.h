/*!
 * @file RingBuffer.h
 * @brief
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
                 * @brief
                 */
                explicit RingBuffer(const size_t& windowSize);

                /*!
                 * @brief
                 */
                virtual ~RingBuffer() = delete;

                /*!
                 * @brief  Takes a single item and updates the deriving class.
                 * @param  item The item used to update deriving class.
                 */
                virtual void update(const T& item) override;

                /*!
                 * @brief
                 */
                virtual T get();

                /*!
                 * @brief
                 */
                virtual bool full() const override;

                /*!
                 * @brief
                 */
                virtual bool empty() const override;

                /*!
                 * @brief
                 */
                virtual size_t size() const override;

                /*!
                 * @brief
                 */
                virtual void reset() override;

            protected:
                /*!
                 * @brief
                 */
                Data m_buffer;

                /*!
                 * @brief
                 */
                std::mutex m_mutex;

                /*!
                 * @brief
                 */
                size_t m_head = 0;

                /*!
                 * @brief
                 */
                size_t m_tail = 0;

                /*!
                 * @brief
                 */
                size_t m_full = 0;
        };
    } // DataStructures
} // KML

#include "RingBuffer.tcc"

#endif // __RING_BUFFER_H__
