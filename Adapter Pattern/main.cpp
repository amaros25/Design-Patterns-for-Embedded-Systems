#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::move;
using std::make_unique;
using std::string;

class Display{

    public:

        virtual void init() noexcept = 0;
        virtual void display(const string& text) noexcept = 0;
        virtual ~Display() = default;

};

class LCD_Display{

    public:

        void init(){
            cout << "init lcd" << endl;
        }

        void display(const string& text){
            cout << "display lcd: " << text << endl;
        }

};

class OLED_Display{

    public:

        void init(){
            cout << "init oled" << endl;
        }

        void display(const string& text){
            cout << "display oled: " << text << endl;
        }

};


class DisplayLcdAdapter: public Display{

        private:

            unique_ptr<LCD_Display> lcd;

        public:

            DisplayLcdAdapter(unique_ptr<LCD_Display> lcd_display): lcd(move(lcd_display)){}

            void init() noexcept override  {
                lcd->init();
            }

            void display(const string& text) noexcept override  {
                lcd->display(text);
            }

};

class DisplayOledAdapter: public Display {
    
    private:

        unique_ptr<OLED_Display> oled;
    
    public:

        DisplayOledAdapter(unique_ptr<OLED_Display> oled_display) : oled(move(oled_display)) {}

        void init() noexcept override {
            oled->init();
        }

        void display(const string& text) noexcept override {
            oled->display(text);
        }

};


int main(){

    auto lcd_display = make_unique<LCD_Display>();
    auto oled_display = make_unique<OLED_Display>();     

    unique_ptr<Display> display1 = make_unique<DisplayLcdAdapter>(move(lcd_display));

    unique_ptr<Display> display2 = make_unique<DisplayOledAdapter>(move(oled_display));

    display1->init();
    display2->init();

    display1->display("Text 1");
    display2->display("Text 2");

    return 0;
    
}