#include <FL/Fl.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <arpa/inet.h>
#include <iostream>
#include <tuple>
#include <string>


class Params
{
  public:
    Params(Fl_Text_Buffer *buff) { buffer = buff; }

    Fl_Text_Buffer *buffer;
};


Fl_Hold_Browser *bro = nullptr;
Fl_Group *group = nullptr;
Fl_Text_Display *chat = nullptr;
Fl_Input *input = nullptr;


void selectGroup(Fl_Widget *, void*)
{
  auto line = bro->value();
  if (line)
  {
    Params *p = (Params *)bro->data(line);
    chat->buffer(p->buffer);
  }
  input->take_focus();
}


void sendMessage(Fl_Widget *, void *v)
{
  auto line = bro->value();
  if (line)
  {
    Params *p = (Params *)bro->data(line);
    p->buffer->append(input->value());
    p->buffer->append("\n");
    input->value("");
  }
  input->take_focus();
}


int main(int argc, char **argv)
{

  Fl_Window *window = new Fl_Window(570, 280);
  window->begin();
  {
    bro = new Fl_Hold_Browser(10, 10, 110, 260);

    group = new Fl_Group(130, 10, 430, 260, "Mekanix");
    group->box(FL_ENGRAVED_BOX);
    group->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP);
    group->labelsize(24);
    group->begin();
    {
        chat = new Fl_Text_Display(135, 40, 420, 200);
        Fl_Text_Buffer *buff = new Fl_Text_Buffer();
        chat->buffer(*buff);
        buff->append("Mekanix: cao\n");
        buff->append("Momo: oj\n");
        input = new Fl_Input(210,245,300,20,"Message:");
        input->take_focus();
        Fl_Button *button = new Fl_Button(510,245,40,20,"Send");
        Params *p = new Params(buff);
        bro->add("Meka", p);
        button->callback(sendMessage, p);
        button->shortcut(FL_Enter);

        buff = new Fl_Text_Buffer();
        p = new Params(buff);
        bro->add("Dervish", p);
    }
    group->end();
    group->show();
    bro->callback(selectGroup);
    bro->select(1);
  }
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
