#define  __NR_write 1
#define __NR_exit 60
#define STDOUT_FILENO 1
void _start()
{
	__asm__ volatile ("call main");
}

static inline long long syscall3(long long syscallnum, long long arg0, long long arg1, long long arg2){
	register long long syscallnum_ __asm__("rax");
	register long long arg0_ __asm__("rdi");
	register long long arg1_ __asm__("rsi");
	register long long arg2_ __asm__("rdx");
	syscallnum_ = syscallnum;
	arg0_ = arg0;
	arg1_ = arg1;
	arg2_ = arg2;
	asm volatile
		(
		 "syscall"
		 : "+r"(syscallnum_)
		 : "r"(arg0_), "r"(arg1_), "r"(arg2_)
		);
	return syscallnum_;
}

static inline long long syscall1 (long long syscallnum, long long arg0){
	register long long syscallnum_ __asm__("rax");
	register long long arg0_ __asm__("rdx");
	syscallnum_ = syscallnum;                                                                                                     arg0_ = arg0;
	asm volatile 
		(
	 	 "syscall"
		 : "+r"(syscallnum_)
		 : "r"(arg0_)
		);
	return syscallnum_;
}

static long long write(int fd, const void *buf, int count){
	return syscall3(__NR_write, fd, (long long)buf, count);
}

static long long exit (int exit_code){
	return syscall1(__NR_exit,exit_code);
}

int main() {
	const char *message = "Hello, World!\n\r";
	int message_length = 14;
	unsigned long long  bytes_written = write(STDOUT_FILENO, message, message_length);
	if (bytes_written == -1) {
		exit(1);
		return 1;
	}
	exit(0);
	return 0;
}

