项目压测

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 1000 -s 30 test.txt
115647 fetches, 1000 max parallel, 4.02452e+07 bytes, in 30.0032 seconds
348 mean bytes/connection
3854.49 fetches/sec, 1.34136e+06 bytes/sec
msecs/connect: 0.716123 mean, 5.76 max, 0.018 min
msecs/first-response: 256.349 mean, 322.161 max, 1.047 min
HTTP response codes:
  code 404 -- 115647
```



# wrk的压测

## 12个thread 30s

3000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c3000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 3000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   140.25ms   13.54ms 255.40ms   85.17%
    Req/Sec     1.78k   334.00     2.53k    68.46%
  635342 requests in 30.09s, 292.65MB read
  Non-2xx or 3xx responses: 635342
Requests/sec:  21113.81
Transfer/sec:      9.73MB
```

4000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c4000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 4000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   185.78ms   27.23ms 495.42ms   81.72%
    Req/Sec     1.79k   596.18     3.36k    64.99%
  637468 requests in 30.10s, 293.63MB read
  Non-2xx or 3xx responses: 637468
Requests/sec:  21180.43
Transfer/sec:      9.76MB
```

7000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c7000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 7000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   321.60ms   25.32ms 538.89ms   77.69%
    Req/Sec     1.81k   712.09     4.44k    64.97%
  637924 requests in 30.09s, 293.84MB read
  Non-2xx or 3xx responses: 637924
Requests/sec:  21203.61
Transfer/sec:      9.77MB
```

8000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c8000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 8000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   320.54ms   45.08ms 552.03ms   62.19%
    Req/Sec     1.96k     1.11k    4.93k    59.25%
  701696 requests in 30.08s, 323.22MB read
  Non-2xx or 3xx responses: 701696
Requests/sec:  23326.99
Transfer/sec:     10.74MB
```

9000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c9000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 9000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   394.57ms   71.72ms 701.60ms   75.95%
    Req/Sec     1.85k     1.10k    5.21k    59.46%
  645112 requests in 30.10s, 297.15MB read
  Non-2xx or 3xx responses: 645112
Requests/sec:  21435.29
Transfer/sec:      9.87MB
```

10000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t12 -c10000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  12 threads and 10000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   407.16ms   60.28ms 666.65ms   65.85%
    Req/Sec     1.97k     1.13k    5.34k    61.07%
  686960 requests in 30.10s, 316.43MB read
  Non-2xx or 3xx responses: 686960
Requests/sec:  22822.34
Transfer/sec:     10.51MB
```





## 3个thread，30s

8000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t3 -c8000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  3 threads and 8000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   321.37ms   42.80ms 456.36ms   66.08%
    Req/Sec     7.80k     4.65k   18.26k    54.44%
  705327 requests in 30.07s, 324.89MB read
  Non-2xx or 3xx responses: 705327
Requests/sec:  23454.67
Transfer/sec:     10.80MB
```



9000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t3 -c9000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  3 threads and 9000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   379.16ms   53.19ms 620.66ms   66.66%
    Req/Sec     7.52k     4.58k   16.19k    56.17%
  672333 requests in 30.06s, 309.69MB read
  Non-2xx or 3xx responses: 672333
Requests/sec:  22368.51
Transfer/sec:     10.30MB
```



## 1个thread，30s

9000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t1 -c9000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  1 threads and 9000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   368.60ms   56.62ms 651.61ms   79.11%
    Req/Sec    22.84k    14.36k   45.28k    55.15%
  687843 requests in 30.05s, 316.84MB read
  Non-2xx or 3xx responses: 687843
Requests/sec:  22886.63
Transfer/sec:     10.54MB
```



request/sec：每秒能够相应的请求数

wrk的使用方法

安装方法：

```shell
git clone git@github.com:wg/wrk.git
cd wrk
apt-get install build-essential -y
make
```





# server开一个io线程，一个worker线程

1个thread，30s

9000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t1 -c9000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  1 threads and 9000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   331.26ms   38.95ms 441.42ms   67.69%
    Req/Sec    25.36k    14.85k   48.37k    52.42%
  763349 requests in 30.02s, 351.62MB read
  Non-2xx or 3xx responses: 763349
Requests/sec:  25431.16
Transfer/sec:     11.71MB
```



10000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t1 -c10000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  1 threads and 10000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   381.30ms   48.55ms 521.84ms   67.98%
    Req/Sec    24.77k    13.32k   47.99k    60.08%
  737995 requests in 30.08s, 339.94MB read
  Non-2xx or 3xx responses: 737995
Requests/sec:  24532.07
Transfer/sec:     11.30MB
```



12000

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/wrk# wrk -t1 -c12000 -d30s http://127.0.0.1:80
Running 30s test @ http://127.0.0.1:80
  1 threads and 12000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   458.50ms   54.99ms 646.52ms   67.03%
    Req/Sec    25.28k    13.66k   49.17k    60.38%
  729433 requests in 30.06s, 335.99MB read
  Non-2xx or 3xx responses: 729433
Requests/sec:  24264.22
Transfer/sec:     11.18MB
```

