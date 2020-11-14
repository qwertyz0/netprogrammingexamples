#include "common_thread.h"

THREAD_HANDLE create_thread(thread_function func, THREAD_PARAM params) {
#ifdef _WIN32
    DWORD hThreadId;
	return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, params, 0, &hThreadId);
#elif __linux__
    return pthread_create(NULL, NULL, func, param);
#else
#error "Unsupported platform"
#endif
}

PROCESS_ID get_process_id() {
#ifdef _WIN32
    return GetCurrentProcessId();
#elif __linux__
    return getpid();
#else
#error "Unsupported platform"
#endif
}

void wait_thread(THREAD_HANDLE handle) {
#ifdef _WIN32
    WaitForSingleObject(handle, INFINITE);
#elif __linux__
    pthread_join(handle, NULL);
#else
#error "Unsupported platform"
#endif
}

void wait_thread(THREAD_HANDLE * handles, int size) {
#ifdef _WIN32
    WaitForMultipleObjects(size, handles, FALSE, INFINITE);
#elif __linux__
    for (int i = 0; i < size; ++i) {
        pthread_join(handles[i], NULL);
    }
#else
#error "Unsupported platform"
#endif
}
