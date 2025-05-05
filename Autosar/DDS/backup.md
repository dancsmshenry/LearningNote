---
title: DDS 协议详解
top: false
cover: false
toc: true
mathjax: true
date: 2025-03-13 21:48:57
password:
summary:
tags:
categories:
---



# 常用缩写

| 缩写                                  | 全称                            |
| ------------------------------------- | ------------------------------- |
| Real-Time Publish Subscribe           | RTPS 实时发布订阅协议           |
| Globally Unique Identifier            | GUID 全局唯一标识符             |
| Participant Discovery Protocol        | PDP 参与者发现协议              |
| Endpoint Discovery Protocol           | EDP 端点发现协议                |
| Simple Participant Discovery Protocol | SPDP 简单参与者发现协议         |
| Simple Endpoint Discovery Protocol    | SEDP 简单端点发现协议           |
| Data-Centric Publisher-Subscriber     | DCPS 以数据为中心的发布订阅模型 |
| Quality of Service                    | QoS 服务质量                    |
| Topic                                 | 主题                            |
| Publisher                             | 发布者                          |
| Subscriber                            | 订阅者                          |
| DataWriter                            | 数据写入者                      |
| DataReader                            | 数据接收者                      |

<br/>

<br/>

<br/>

# DCPS

## Domain

包含了 domainparticipant，是服务的入口，是许多类的工厂，也是其他对象的容器

<br/>

## Infrastructure

包含了一些基本类型和抽象类，比如 condition，qos 等

<br/>

## Publication

发布模块，包含了 publisher 和 datawriter，publisherlistener 和 datawriterlistener

<br/>

## Subscription

<br/>

## Topic

<br/>

<br/>

# RTPS

## Structure module

主要介绍了 rtps 层的各个 entity，并且会与上层 dcps 中各个实体进行映射

<br/>

## Message module

主要介绍了一条消息的各个组成，比如说 submessage 的 submessageheader，submessageelement

<br/>

## Behavior module

主要介绍了一条消息的传递中，各个接口是如何做关联的，以及 stateless 和 stateful。同时介绍了消息的分片，wlp 保活机制

<br/>

## Discovery module

主要介绍了端点和参与者的发现机制

分为两个部分：Participant Discovery Protocol （PDP）和 Endpoint Discovery Protocol（EDP），两个协议本质上是相互独立的

PDP 协议是用于在网络总线上，帮助两个参与者进行相互发现的。二者相互发现成功后，使用 SEDP 交换持有的 endpoint 信息

在 rtps 层，有四个内置的 topic，dcpsParticipant, dcpsSubscription, dcpsPublication, dcpsTopic，其中都有对应的 datawriter 和 datareader；内置的 writer 和 reader，是用来发布一些 detail 信息的

其中的 dcpsParticipant 是用来做 participant 的相互发现的，也就是 spdp。而后的 dcpsSubscription，dcpsPublication 和 dcpsTopic 是用来做 sedp 的，也就是 本地的 topic，reader 和 writer 的相互发现

对于每个参与者，都会创建两个内置的 endpoint，SPDPbuiltinParticipantWriter 和 SPDPbuiltinParticipantReader。对于 writer 来说，里面始终只有一条 change，记录的是当前 participant 的一些配置属性，一旦有发生变化，则会有新的 change 替换