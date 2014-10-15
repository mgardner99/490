

#include "Communication.h"

//note there is a lot of name hiding in this method... dont get confused
//static!
QStringList Communication::getPortsList(){
    io_service io;
    QStringList ports;

    for(int i = 0; i < 20; i++){
        try{
            stringstream portName;
            portName<<"COM"<<i;
            serial_port port(io,portName.str());
            port.close();
            ports << portName.str().c_str();
        }
        catch(...){

        }
    }
    return ports;
}
Communication::~Communication(){
    cout<<"coms killed"<<endl;
    port->close();
    file<<endl<<"end";
    file.close();
    delete port;
    io->stop();
    delete io;
    delete data;
}

//you will need to change
Communication::Communication(string comPort): q(),file("C:\\Users\\Megan Gardner\\GitHub\\490\\logOutput.log",ios::out)
{
    mutex = false;
    file<<"begin"<<endl;
    io = new io_service();
    port = new serial_port(*io,comPort);
    //port->set_option(serial_port_base::baud_rate(9600));
    port->set_option(serial_port_base::baud_rate(57600)); //to match baud rate of acc/gyro

    data = new vector<DataPoint>();
    data->push_back(DataPoint(QPoint(99,65),0)); //remove these when you have actual data
    data->push_back(DataPoint(QPoint(115,117),0));
    data->push_back(DataPoint(QPoint(35,158),0)); //remove these when you have actual data
    data->push_back(DataPoint(QPoint(93,214),0));
    data->push_back(DataPoint(QPoint(47,244),0)); //remove these when you have actual data
    data->push_back(DataPoint(QPoint(85,324),0));

    if(port->is_open())
        cout<<"Opened "<<comPort<<endl;
}

void Communication::update(){
    if(mutex == true)
        return; //mutex WOOT
    cout<<"in update"<<endl;
    mutex = true;

    readData();

    int fudgeFix = 0;
    while(!q.empty()){

        switch (q.front()){
        case 'a': dataSet(0);
            break;
        case 'b': dataSet(1);
            break;
        case 'c': dataSet(2);
            break;
        case 'd': dataSet(3);
            break;
        case 'e': dataSet(4);
            break;
        case 'f': dataSet(5);
            break;
        case 'g': getAngle(1,1);
            break;
        case 'h': getAngle(1,2);
            break;
        case 'i': getAngle(1,3);
            break;
        case 'j': getAngle(2,1);
            break;
        case 'k': getAngle(2,2);
            break;
        case 'l': getAngle(2,3);
            break;
        default:
            q.pop();
            cout<<"Something went wrong..."<<endl;
            break;
        }

        fudgeFix++;
        if (fudgeFix > 20){
            int qsz = q.size();
            for(int i = 0; i < qsz; i++)
                q.pop();
            mutex = false;
            break;
        }
    }
    mutex = false;
    cout<<"out update"<<endl;
}

void Communication::dataSet(int sense){
    stringstream ss;
    ss<<0;
    cout<<"in dataSet"<<endl;
    if(q.size() != 0)
    q.pop();
    cout<<"before while"<<endl;
    while(q.front() != 'z'){ // 'z' is the end packet footer
        if(q.size() == 0)
            return;
        cout<<"getting q head"<<endl;
        ss<<q.front();
        cout<<"got q head"<<endl;
        if(q.size()!=0)
        q.pop();
        cout<<q.size()<<endl;
        if(q.size() == 0)
            return;
    }
    cout<<"after while"<<endl;

    if(q.size()!=0)
        q.pop();
    cout<<"pre string stream"<<endl;
    if(ss.rdbuf()->in_avail()>0)
        data->at(sense).setVal(atoi(ss.str().c_str()));
    cout<<"post string stream "<<ss.str().c_str()<<endl;
    cout<<"out dataSet"<<endl;
}

//fairly convoluted way of reading the incoming datastream from the arduino... YAY
void Communication::readData(){
    cout<<"in read data"<<endl;
    static int size = 0;

    try{
        cout<<"reading data"<<endl;
        size = port->read_some(buffer(msg,512));
        cout<<size<<endl; // debugging
        cout<<"data read"<<endl;
    }
    catch(...){
        //fixes a crash where if the thread terminates the program dies
    }

    cout<<"pushing data"<<endl;
    for(int i = 0; i < size; i++){
        q.push(msg[i]);
        if(msg[i]== 'a'){
            file<<endl;
            file<<time(NULL);
        }
        file<<msg[i];
    }
    cout<<"data pushed"<<endl;

    cout<<"checking overflow"<<endl;
    if(q.size() > 100){
        int qsize=q.size();
        cout<<"inner loop 1"<<endl;
        for (int i = 0; i < qsize; i++){
            cout<<"inner loop 2"<<endl;
            q.pop();
        }
        cout<<"Over Flow"<<endl;
        return;
    }
    cout<<"checked overflow"<<endl;

    cout<<"finding front"<<endl;
    findFront(); //when the transmission is recieved the first time, you can get a middle of a packet.
    cout<<"front found"<<endl;

    if(q.size() < 6){ //data will be a 6 byte packet
        readData();
    }
    cout<<"out read data"<<endl;
}

vector<DataPoint>* Communication::getData(){
    return data;
}

void Communication::findFront(){
    if(q.size() > 0){
        if((q.front() != 'a') && (q.front() != 'b') && (q.front() != 'c') && (q.front() != 'd') && (q.front() != 'e') && (q.front() != 'f') && (q.front() != 'g')  && (q.front() != 'h') && (q.front() != 'i') && (q.front() != 'j') && (q.front() != 'k') && (q.front() != 'l')){
            q.pop();
            findFront();
        }
    }

}

//written to get yaw data
void Communication::getAngle(int sensor, int dir){
    // dir: 0=x, 1=y, 2=z
    cout << "in getAngle" << endl;
    stringstream ss;
    if(q.size() != 0)
    q.pop();
    cout<<"before while"<<endl;
    while(q.front() != 'z'){ // 'z' is the end packet footer
        if(q.size() == 0)
            return;
        ss<<q.front();
        if(q.size()!=0)
        q.pop();
        cout<<q.size()<<endl;
        if(q.size() == 0)
            return;
    }
    cout<<"after while"<<endl;

    if(q.size()!=0)
        q.pop();

    // stringstream to float conversion - convoluded but actually easiest to go ss->QStr->float
    float in = 0.0;
    QString QStr = QString::fromStdString(ss.str());
    in = QStr.toFloat();
    if(sensor==1)
    {
        cout << "dir:" <<endl;
        cout << dir << endl;
        if(dir==1)
        {
            k1.setX(in);
            cout << "set x" << endl;
            cout << k1.getX() << endl;
        }
        else if(dir==2)
        {
            cout<<"set y"<<endl;
            k1.setY(in);
        }
        else
        {
            cout<<"set z"<<endl;
            k1.setZ(in);
        }
    }
    else if(sensor==2)
    {
        if(dir==1)
            k2.setX(in);
        else if(dir==2)
            k2.setY(in);
        else
            k2.setZ(in);
    }
    cout<<"out angleOut"<<endl;
}

KneeVec Communication::getAngleData1()
{
    return k1;
}

KneeVec Communication::getAngleData2()
{
    return k2;
}
