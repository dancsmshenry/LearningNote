- 一个channel被放入loop的过程：

- channel::update -> eventloop::updatechannel -> poller::updatechannel



- channel::update是private的，那是如何被调用的？

- 是在enableReading,disableReading等函数中被调用的....



- 一个channel从loop中移除的过程：

- channel::remove -> eventloop::removechannel -> poller::removechannel



- 有点没搞懂tie函数是干啥的？