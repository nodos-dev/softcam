#include <softcamcore/SenderAPI.h>
#include <gtest/gtest.h>

#include <softcamcore/FrameBuffer.h>
#include <atomic>
#include <thread>
#include <chrono>


namespace {
namespace sc = softcam;
namespace sender = softcam::sender;

#define SLEEP(msec) \
        std::this_thread::sleep_for(std::chrono::milliseconds(msec))
#define WAIT_FOR_FLAG_CHANGE(atomic_flag, last_value) [&]{ \
            while (atomic_flag == last_value) { SLEEP(1); } \
        }()

TEST(SendFrame, Basic)
{
    const float TIMEOUT = 1.0f;
    const unsigned char COLOR_VALUE = 123;

    auto handle = sender::CreateCamera(320, 240);
    std::atomic<int> flag = 0;

    std::thread th([&]
    {
        auto fb = sc::FrameBuffer::open();
        ASSERT_TRUE( fb );

        EXPECT_EQ( fb.frameCounter(), 0 );
        flag = 1;

        fb.waitForNewFrame(0, TIMEOUT);
        EXPECT_EQ( fb.frameCounter(), 1 );

        unsigned char image[320 * 240 * 3];
        uint64_t frame_counter = 0;
        fb.transferToDIB(image, &frame_counter);
        EXPECT_EQ( image[0], COLOR_VALUE );
        EXPECT_EQ( image[320 * 240 * 3 - 1], COLOR_VALUE );
        EXPECT_EQ( frame_counter, 1 );
    });

    WAIT_FOR_FLAG_CHANGE(flag, 0);

    unsigned char image[320 * 240 * 3] = {};
    std::memset(image, COLOR_VALUE, sizeof(image));
    sender::SendFrame(handle, image);

    th.join();
    sender::DeleteCamera(handle);
}

TEST(WaitForConnection, ShouldBlockUntilReceiverConnected)
{
    auto handle = sender::CreateCamera(320, 240);
    std::atomic<int> flag = 0;

    std::thread th([&]
    {
        WAIT_FOR_FLAG_CHANGE(flag, 0);
        SLEEP(10);
        EXPECT_EQ( flag, 1 );

        auto fb = sc::FrameBuffer::open();
        ASSERT_TRUE( fb );

        WAIT_FOR_FLAG_CHANGE(flag, 1);
        EXPECT_EQ( flag, 2 );
    });

    flag = 1;
    bool ret = sender::WaitForConnection(handle);
    flag = 2;

    th.join();
    EXPECT_EQ( ret, true );
    sender::DeleteCamera(handle);
}

TEST(WaitForConnection, ShouldTimeout)
{
    const float TIMEOUT = 0.5f;

    auto handle = sender::CreateCamera(320, 240);
    std::atomic<int> flag = 0;

    std::thread th([&]
    {
        WAIT_FOR_FLAG_CHANGE(flag, 0);
        SLEEP(10);
        EXPECT_EQ( flag, 1 );

        WAIT_FOR_FLAG_CHANGE(flag, 1);
        EXPECT_EQ( flag, 2 );
    });

    flag = 1;
    bool ret = sender::WaitForConnection(handle, TIMEOUT);
    flag = 2;

    th.join();
    EXPECT_EQ( ret, false );
    sender::DeleteCamera(handle);
}

TEST(WaitForConnection, InvalidArgs)
{
    bool ret = sender::WaitForConnection(nullptr);
    EXPECT_EQ( ret, false );

    auto handle = sender::CreateCamera(320, 240);
    sender::DeleteCamera(handle);

    ret = sender::WaitForConnection(handle);
    EXPECT_EQ( ret, false );
}

} //namespace