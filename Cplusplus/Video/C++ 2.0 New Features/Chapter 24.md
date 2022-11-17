# Perfect Forwarding

- unperfect forwarding

  - ```cpp
    void process(int& i){
        cout << "int& i = " << i << endl;
    }
    
    void process(int&& i){
        cout << "int&& i = " << i << endl;
    }
    
    ina a = 0;
    
    process(a);//a被当作左值处理
    process(1);//1被当作右值处理
    process(move(a));//move使得变为右值，当作右值处理
    
    void forward(int&& i){
        cout << "forward(int&&)" << endl;
        process(i);
    }
    
    forward(2);//以右值的方式传入forward，但是最后却是以左值的方式传入process,原因：传递过程中它变成了一个named object
    forward(move(a));//理由同上，最后都是以左值的方式传入process
    forward(a);//error，左值根本调用不起来
    ```

  - 起初的目标：想要设计一个类型，它的值是可以被偷的，从而大幅提高容器的效率
