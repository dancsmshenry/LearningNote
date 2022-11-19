eventloop是如何退出loop的

- 第一种情况用户调用loop()后，可以在后面给个定时器，定时10s后调用quit()，从而退出loop
- 第二种情况，别的线程希望停止当前这个loop，于是将该loop的quit通过runinloop传入给当前的loop；这样后续loop就可以消费其中的callback，从而停止loop
- 针对第二种情况，所以会先判断当前的线程是不是loop对应的thread，如果不是的话，就需要调用wakeup，把loop唤醒，从而消费函数



runinloop的用处

- 停止当前loop（传入quit()）
- accept()