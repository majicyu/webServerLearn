bool daemonize(){
    //创建子进程，关闭父进程，这样可以使程序在后台运行
    pid_t pid = frok();
    if(pid < 0){
        return false;
    }
    else if(pid < 0){
        exit(0);
    }
    //设置文件权限掩码，当进程创建新文件
    umask(0);

    //创建新的会话，创建本进程为进程祖的首领
    pid_t sid = setsid();
    if(sid<0){
        return false;
    }

    //切换工作目录
    if((chdir("/"))<0){
        return false;
    }

    //关闭标准输入，输出，错误输出设备
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null",O_RDONLY);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_REWR);
    return true;
}
