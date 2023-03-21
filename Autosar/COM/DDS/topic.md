topic_description
- string topic_name topic的名字
- string type_name


topic
- 继承自**domain_entity**和**topic_description**
- domainparticipant* 指向参与者的指针
- topicqos 当前topic的qos
- shared_ptr<topiclistener>


typesupport
- 继承自enable_shared_from_this，表示可以将当前类作为共享指针在其成员函数内使用


topic_type
- 我理解他是topic的类型？
- string topic_type_name


topic_listener
- topic的listener