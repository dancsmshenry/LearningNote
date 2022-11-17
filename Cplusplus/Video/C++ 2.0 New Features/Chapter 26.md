# Move-aware class对容器的效能测试

- 只要是以结点形式存在的，move construct和copy construct都是一样的
- 针对vector，deque，list等容器进行了move construct测试，发现性能有显著的提升
