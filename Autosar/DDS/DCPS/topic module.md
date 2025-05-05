# topic_description

string `topic_name` topic的名字

string `type_name`

<br/>

<br/>

<br/>

# topic

继承自 **domain_entity** 和 **topic_description**

domainparticipant* 指向参与者的指针

topicqos 当前 topic 的 qos

shared_ptr<topiclistener>

<br/>

<br/>

<br/>

# typesupport

继承自 enable_shared_from_this，表示可以将当前类作为共享指针在其成员函数内使用

<br/>

<br/>

<br/>

# topic_type

string `topic_type_name` topic 的类型

<br/>

<br/>

<br/>

# topic_listener

topic 的 listener