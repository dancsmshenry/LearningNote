# domain_participant

继承自 entity

- `domain_id`
- `participant_id`
- `domain_participant_qos`
- `domain_participant_listener`
- `rtps_participant`
- `map<string, weak_ptr<topic>> topics_`（存放 topic）
- `map<instancehandle, weak_ptr<publisher>> publishers_`（存放 publisher）
- `map<instancehandle, weak_ptr<subscriber>> subscribers_`（存放 subscriber）
- `default_publisher_qos`（pub 端默认的 qos）
- `default_subscriber_qos`（sub 端默认的 qos）
- `builtin_subscriber_`
- `builtin_publisher_`
- `map<string, shared_ptr<topic>> builtin_topics_`（存储当前 domain_participant 中所有的 builtin topics）

<br/>

<br/>

<br/>

# domain_participant_factory

单例模式

- `map<domainid, vector<weak_ptr<domainparticipant>>> participants_` 存放每个 domain 里面的 participant
- `map<domainid, shared_ptr<rtps::domain>> rtps_domains_` 将 DCPS 的 domain 和 RTPS 的 domain 进行映射
- `domain_participant_factory_qos`
- `domain_participant_default_qos`

<br/>

<br/>

<br/>

# domain_participant_listener

继承自 publisherlistener，subscriberlistener，topiclistener