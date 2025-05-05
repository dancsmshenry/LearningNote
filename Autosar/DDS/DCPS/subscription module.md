# subscriber

## number
`domainparticipant* participant_` 指向 participant 的指针

`subscriberqos qos_` sub 端的 qos 策略

`map<string, vector<weak_ptr<datareader>>> readers_` 存放不同 topic 下的 datareader

`subscriberlistener`

`map<string, shared_ptr<datareader>> builtin_readers_` 存放内置 topic 的 datareader

- 每个 builtin topic 都只有一个DR

`default_datareader_qos` （每个DR都有会默认的 qos）

<br/>

## function

`enable()` 循环调用 readers_ 的 enable

`disable()` 循环调用 readers_ 的 disable

setqos：判断是否符合切换qos的要求；并且会更新其下面所有topic中所有的DR的qos

`shared<DataReader> createdatareader` 根据对应的 reader_qos， topic 和 listener 生成对应的 reader

`notifydatareaders()`

<br/>

<br/>

<br/>

# datareader

继承自 DomainEntity

<br/>

## number
`subscriber*` 指向 sub 端的指针

`shared_ptr<rtps::reader>` 对应 `RTPS` 的 reader

`shared_ptr<topicdescription>` 存放 topic 的相关信息

- 至于为什么在 datawriter 端存放的是 topic ，因为 topic 是继承自 domainentity 和 topicdescription 的
- 并且 topicdescription 是一个虚基类，因此这里必定是父类指针指向子类指针
- 那如何找到其对于的 qos ，我理解就是它有个接口 getparticipant ，可以找到对应的 participant ，从而找到真正的 topic ，也就找到了其 qos 

`shared_ptr<rtps::readerHistory>` 存放 cachechange

- 感觉是代码没写完，因为对应的 writer 在上层新建了一个 DataWriterHistory ，继承自 rtps::WriterHistory

`shared_ptr<innerreaderlistener>`，有一个指向 datareader 的指针

`shared_ptr<DataReaderListener>`

`DataReaderQos qos_`  DR 端的 qos

`Guid guid_` 全局 id

<br/>

## function

`enable()` 在内部组装 rtps::reader 的属性，涉及到一些底层的 qos 策略