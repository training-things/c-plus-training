#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <atomic>
#include <memory>

using namespace std;

#ifndef SRC_MUTEX_H_
#define SRC_MUTEX_H_

class Status
{
private:
    /* data */
public:
    Status(/* args */);
    ~Status();
};

Status::Status(/* args */)
{
}

Status::~Status()
{
}

class Mutex
{
public:
    virtual ~Mutex() {}

    // Attempt to acquire lock.  Return OK on success, or other Status on failure.
    // If returned status is OK, BlackWidow will eventually call UnLock().
    virtual Status Lock() = 0;

    // Attempt to acquire lock.  If timeout is non-negative, operation may be
    // failed after this many microseconds.
    // Returns OK on success,
    //         TimedOut if timed out,
    //         or other Status on failure.
    // If returned status is OK, BlackWidow will eventually call UnLock().
    virtual Status TryLockFor(int64_t timeout_time) = 0;

    // Unlock Mutex that was successfully locked by Lock() or TryLockUntil()
    virtual void UnLock() = 0;
};

class CondVar
{
public:
    virtual ~CondVar() {}

    // Block current thread until condition variable is notified by a call to
    // Notify() or NotifyAll().  Wait() will be called with mutex locked.
    // Returns OK if notified.
    // Returns non-OK if BlackWidow should stop waiting and fail the operation.
    // May return OK spuriously even if not notified.
    virtual Status Wait(std::shared_ptr<Mutex> mutex) = 0;

    // Block current thread until condition variable is notified by a call to
    // Notify() or NotifyAll(), or if the timeout is reached.
    // Wait() will be called with mutex locked.
    //
    // If timeout is non-negative, operation should be failed after this many
    // microseconds.
    // If implementing a custom version of this class, the implementation may
    // choose to ignore the timeout.
    //
    // Returns OK if notified.
    // Returns TimedOut if timeout is reached.
    // Returns other status if BlackWidow should otherwis stop waiting and
    //  fail the operation.
    // May return OK spuriously even if not notified.
    virtual Status WaitFor(std::shared_ptr<Mutex> mutex,
                           int64_t timeout_time) = 0;

    // If any threads are waiting on *this, unblock at least one of the
    // waiting threads.
    virtual void Notify() = 0;

    // Unblocks all threads waiting on *this.
    virtual void NotifyAll() = 0;
};

// Factory class that can allocate mutexes and condition variables.
class MutexFactory
{
public:
    // Create a Mutex object.
    virtual std::shared_ptr<Mutex> AllocateMutex() = 0;

    // Create a CondVar object.
    virtual std::shared_ptr<CondVar> AllocateCondVar() = 0;

    virtual ~MutexFactory() {}
};
#endif // SRC_MUTEX_H_

class LockInfo
{

private:
    uint16_t _runningModes;
    uint16_t _pendingModes;
    std::vector<uint16_t> _runningRefCnt;
    std::vector<uint16_t> _pendingRefCnt;
};

struct LockMapStripe
{
    // Mutex must be held before modifying keys map
    // std::shared_ptr<Mutex> stripe_mutex;
    // Condition Variable per stripe for waiting on a lock
    // std::shared_ptr<CondVar> stripe_cv;
    // Locked keys use std::unordered_set  std::unordered_map
    // std::unordered_set<std::string> keys;
    std::unordered_set<int8_t> keysInt;
    // std::unordered_map<std::string, LockInfo>; // 可以存储其他信息
};

int main()
{
    std::shared_ptr<Mutex> stripe_mutex;
    std::shared_ptr<CondVar> stripe_cv;
    LockMapStripe lockMap;


    cout << "stripe_mutex sizeof: " << sizeof stripe_mutex << endl;
    cout << "stripe_cv sizeof: " << sizeof stripe_cv << endl;
    cout << "LockMapStripe sizeof: " << sizeof lockMap << endl;


    // https://stackoverflow.com/questions/6826402/why-is-the-size-of-make-shared-two-pointers
    /**
        stripe_mutex sizeof: 16
        stripe_cv sizeof: 16
        LockMapStripe sizeof: 32
     */

    // std::unordered_set vs std::unordered_map 
    // https://chromium.googlesource.com/chromium/src/+/HEAD/base/containers/README.md#std_unordered_map-and-std_unordered_set
}