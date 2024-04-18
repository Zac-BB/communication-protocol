struct pose{
    // 00 is i 000 is J 000 is theta
    uint8_t Pose;
    pose(uint8_t i, uint8_t j, uint8_t t) {
        Pose = (i << 6) | (j << 3) | (t);
    }
    pose() {
        Pose = 0x00;
    }
    pose(uint8_t casted) {
        Pose = casted;
    }
    uint8_t getI() {

        return (Pose >> 6) & 0x03;
    }
    void setI(uint8_t i){
        Pose &= 0x3f;
        Pose |= (i << 6);
    }
    uint8_t getJ() {
        return (Pose >> 3) & 0x07;
    }
    void setJ(uint8_t j){
        Pose &= 0xc7;
        Pose |= (j << 3);
    }
    uint8_t getT() {
        return (Pose) & 0x07;
    }
    void setT(uint8_t t){
        Pose &= 0xf8;
        Pose |= (t);
    }
    bool cordsMatch(pose& b) {
        return getI() == b.getI() && getJ() == b.getJ();
    }
    static int hash(pose self) {
        return (int)(self.getI()) * 6 + (int)(self.getJ());
    }
    operator uint8_t() {
        return Pose;
    }
    bool operator == (const pose& comp) {
        return (Pose & 0xf8) == (comp.Pose & 0xf8);
    }
    bool operator == (const uint8_t& comp) {
        return (Pose & 0xf8) == (comp & 0xf8);
    }
    void print() {
        // Serial.print((int)getI());
        // Serial.print(",");
        // Serial.println((int)getJ());
        // std::cout << "( " << (int)getI() << " , " << (int)getJ() << " )" << std::endl;
    }
};
class node {
    
    public:
        uint8_t val = 0x00;
        node(uint8_t in);
        node(bool hasNorth, bool hasEast, bool hasSouth, bool hasWest);
        node();
        void setDir(bool wall, uint8_t dir);
        void adjacentSet(bool wall,uint8_t dir);
        bool getDir(uint8_t dir);
        void setFeature(uint8_t face);
        bool getFeature(uint8_t& face);
        bool explored();
        operator uint8_t() {
            return val;
        }

};

struct nav {
    // priority(0000) turn(000) drive(0)
    uint8_t data;
    nav(uint8_t dir) {
        data = dir;
    }
    nav(){
        data = 0x00;
    }
    //priority is 0x01-> 0x1f turn if 0x00

    nav(uint8_t priority, uint8_t turn, uint8_t drive) {
        data = (priority << 4) | (turn << 1) | drive;
    }
    uint8_t turnDir() {
        return (data >> 1) & 0x07;
    }
    bool drive() {
        return (data) & 0x01;
    }
    uint8_t priority() {
        return (data >> 4) & 0x0f;
    }

    operator uint8_t() {
        return data;
    }
};
