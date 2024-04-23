#pragma once


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

struct nav {
    // priority(0000) turn(000) drive(0)
    uint8_t data;
    const static uint8_t init = 0x00;
    nav(uint8_t dir) {
        data = dir;
    }
    nav(){
        data = init;
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

struct mapData {
    // 00 is i 000 is J 00 is theta 0 is wall
    uint8_t data = 0x00;
    mapData( uint8_t i, uint8_t j, uint8_t t,uint8_t wall) {
        data = (i << 6) | (j << 3) | (t << 1) | wall;
    }
    mapData(void) {
        data = 0x00;
    }
    mapData(uint8_t casted) {
        data = casted;
    }
    uint8_t getI() {

        return (data >> 6) & 0x03;
    }
    void setI(uint8_t i){
        data &= 0x3f;
        data |= (i << 6);
    }
    uint8_t getJ() {
        return (data >> 3) & 0x07;
    }
    void setJ(uint8_t j){
        data &= 0xc7;
        data |= (j << 3);
    }
    uint8_t getT() {
        return (data >> 1) & 0x03;
    }
    void setT(uint8_t t){
        data &= 0xf9;
        data |= (t << 1);
    }
    uint8_t getWall() {
        return (data ) & 0x01;
    }
    void setWall(uint8_t wall){
        data &= 0xfe;
        data |= (wall & 0x01);
    }
    bool cordsMatch(mapData& b) {
        return getI() == b.getI() && getJ() == b.getJ();
    }
    
    operator uint8_t() {
        return data;
    }
    bool operator == (const mapData& comp) {
        return (data & 0xf8) == (comp.data & 0xf8);
    }
    bool operator == (const uint8_t& comp) {
        return (data & 0xf8) == (comp & 0xf8);
    }
   
};

struct featureData{
    //assessable via cell data lsb is for type
    // ramp i [00] j[000] t[00] Type[~0~]
    // button i [00] j[000] t[00] Type[~1~]
    uint8_t data = 0x00;
    mapData( uint8_t i, uint8_t j, uint8_t t,uint8_t type) {
        data = (i << 6) | (j << 3) | (t << 1) | type;
    }
    mapData(void) {
        data = 0x00;
    }
    mapData(uint8_t casted) {
        data = casted;
    }
    uint8_t getI() {

        return (data >> 6) & 0x03;
    }
    void setI(uint8_t i){
        data &= 0x3f;
        data |= (i << 6);
    }
    uint8_t getJ() {
        return (data >> 3) & 0x07;
    }
    void setJ(uint8_t j){
        data &= 0xc7;
        data |= (j << 3);
    }
    uint8_t getT() {
        return (data >> 1) & 0x03;
    }
    void setT(uint8_t t){
        data &= 0xf9;
        data |= (t << 1);
    }
    uint8_t getWall() {
        return (data ) & 0x01;
    }
    void setWall(uint8_t wall){
        data &= 0xfe;
        data |= (wall & 0x01);
    }
    bool cordsMatch(mapData& b) {
        return getI() == b.getI() && getJ() == b.getJ();
    }
    
    operator uint8_t() {
        return data;
    }
    bool operator == (const mapData& comp) {
        return (data & 0xf8) == (comp.data & 0xf8);
    }
    bool operator == (const uint8_t& comp) {
        return (data & 0xf8) == (comp & 0xf8);
    }
}

