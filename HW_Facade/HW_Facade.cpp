
#include <iostream>
#include <string>

class Projector
{
private:
    bool power;
public:
    Projector()
    {
        power = false;
    }
    void turnOn()
    {
        power = true;
    }
    void turnOff()
    {
        power = false;
    }
    bool getPower() const
    {
        return power;
    }
};
class SoundSystem
{
private:
    int volume;
    bool power;
public:
    SoundSystem()
    {
        volume = 50;
        power = false;
    }
    void turnOn()
    {
        power = true;
    }
    void turnOff()
    {
        power = false;
    }
    void changeVolume(int volumeChange)
    {
        if (volumeChange < 0)
        {
            volumeChange *= -1;
            volumeDecrease(volumeChange);
        }
        else
        {
            volumeIncrease(volumeChange);
        }
    }
    void volumeDecrease(int number)
    {
        volume -= number;
        if (volume < 0)
        {
            volume = 0;
        }
    }
    void volumeIncrease(int number)
    {
        volume += number;
        if (volume > 100)
        {
            volume = 100;
        }
    }
    int getVolume() const
    {
        return volume;
    }
    int getPower() const
    {
        return power;
    }
};
class DVDPlayer
{
private:
    std::string currentDVD;
    bool power;
public:
    DVDPlayer()
    {
        currentDVD = "none";
        power = false;
    }
    void turnOn()
    {
        power = true;
    }
    void turnOff()
    {
        power = false;
    }
    void insertDVD(std::string DVD)
    {
        if (currentDVD != "none")
        {
            drawOutDVD();
        }
        currentDVD = DVD;
    }
    void drawOutDVD()
    {
        currentDVD = "none";
    }
    std::string getDVD() const
    {
        return currentDVD;
    }
    bool getPower()
    {
        return power;
    }
};
class Screen
{
private:
    bool deployed;
public:
    Screen()
    {
        deployed = false;
    }
    void deploy()
    {
        deployed = true;
    }
    void undeploy()
    {
        deployed = false;
    }
    bool isDeployed()
    {
        return deployed;
    }
};

class Facade
{
protected:
    Projector* _Projector;
    SoundSystem* _SoundSystem;
    DVDPlayer* _DVDPlayer;
    Screen* _Screen;
public:
    Facade()
    {
        _Projector = new Projector;
        _SoundSystem = new SoundSystem;
        _DVDPlayer = new DVDPlayer;
        _Screen = new Screen;
    }
    ~Facade()
    {
        delete _Projector;
        delete _SoundSystem;
        delete _DVDPlayer;
        delete _Screen;
    }
    void turnOn()
    {
        _Projector->turnOn();
        _SoundSystem->turnOn();
        _DVDPlayer->turnOn();
        _Screen->deploy();
    }
    void turnOff()
    {
        _Projector->turnOff();
        _SoundSystem->turnOff();
        _DVDPlayer->turnOff();
        _Screen->undeploy();
    }
    void changeVolume(int volume)
    {
        _SoundSystem->changeVolume(volume);
    }
    void insertDVD(std::string DVD)
    {
        _DVDPlayer->insertDVD(DVD);
    }
    void info()
    {
        std::cout << "Projector:\nPower: " << _Projector->getPower() << "\nSound System:\nPower: " << _SoundSystem->getPower() <<
            "\nVolume: " << _SoundSystem->getVolume() << "\nDVD Player:\nPower: " << _DVDPlayer->getPower() << "\nDVD: " <<
            _DVDPlayer->getDVD() << "\nScreen:\nDeployed: " << _Screen->isDeployed() << "\n";
    }
};

class Client
{
private:
    Facade* facade;
public:
    Client(Facade* _facade)
    {
        facade = _facade;
    }
    void turnOn()
    {
        facade->turnOn();
    }
    void turnOff()
    {
        facade->turnOff();
    }
    void changeVolume(int volume)
    {
        facade->changeVolume(volume);
    }
    void insertDVD(std::string DVD)
    {
        facade->insertDVD(DVD);
    }
    void info()
    {
        facade->info();
    }
};

int main()
{
    Facade* facade = new Facade;
    Client client(facade);
    client.info();
    client.turnOn();
    client.insertDVD("NewFilm");
    client.changeVolume(20);
    std::cout << "\n\n";
    client.info();
    delete facade;
}