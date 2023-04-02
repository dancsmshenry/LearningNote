domain_participant
- 继承自entity
- domain_id
- participant_id
- domain_participant_qos
- domain_participant_listener
- rtps_participant
- map<string, weak_ptr<topic>> topics_（存放topics）
- map<instancehandle, weak_ptr<publisher>> publishers_（存放publishers）
- map<instancehandle, weak_ptr<subscriber>> subscribers_（存放subscribers）
- default_publisher_qos（pub端默认的qos）
- default_subscriber_qos（sub端默认的qos）
- builtin_subscriber_
- builtin_publisher_
- map<string, shared_ptr<topic>> builtin_topics_（用于存储当前domain_participant中所有的topics）


<br/>


domain_participant_factory（单例模式；用户使用它的getparticipant()获取participant实例）
- `map<domainid, vector<weak_ptr<domainparticipant>>> participants_` 存放每个domain里面的participant
- `map<domainid, shared_ptr <rtps::domain>> rtps_domains_` 将dcps层的domain和rtps层的domain进行映射
- domain_participant_factory_qos
- domain_participant_default_qos

<br/>


domain_participant_listener
- 继承自publisherlistener，subscriberlistener,topiclistener（dds规范要求）