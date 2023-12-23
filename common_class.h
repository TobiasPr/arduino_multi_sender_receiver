class CommonClass {
  public:
    bool printInfo;

    CommonClass(bool print = false): printInfo(print){}
    
    virtual void init();  

    void printIfConfigured(String value){
      if(printInfo){
        Serial.println(value);
      }
    }
};