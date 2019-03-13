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
Fl_Group *chatgroup = nullptr;
Fl_Group *textgroup = nullptr;
Fl_Group *contactsgroup= nullptr;
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

  Fl_Window *window = new Fl_Window(490, 280);
  window->resizable(*window);
  window->begin();
  {

    contactsgroup = new Fl_Group(10, 10, 110, 260);
    chatgroup = new Fl_Group(130, 10, 350, 230);
    textgroup = new Fl_Group(130,245,330,20);

    // textgroup->resizable(nullptr);
    // contactsgroup->resizable(nullptr);

    // chatgroup->box(FL_ENGRAVED_BOX);
    // chatgroup->align(FL_ALIGN_INSIDE|FL_ALIGN_TOP);
    // chatgroup->labelsize(24);

    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Params *p = new Params(buff);
    contactsgroup->begin();
    {
      bro = new Fl_Hold_Browser(10, 10, 110, 260);
      bro->add("Meka", p);
      bro->add("Dervish", p);
    }
    contactsgroup->end();
    chatgroup->begin();
    {
        chat = new Fl_Text_Display(130, 10, 350, 230);
        buff = new Fl_Text_Buffer();
        p = new Params(buff);
    }
    chatgroup->end();
    textgroup->begin();
    {
        input = new Fl_Input(130,245,300,20);
        input->take_focus();
        Fl_Button *button = new Fl_Button(440,245,40,20,"Send");
        button->callback(sendMessage, p);
        button->shortcut(FL_Enter);
    }
    textgroup->end();
    bro->callback(selectGroup);
    bro->select(1);
    contactsgroup->show();
    chatgroup->show();
    textgroup->show();
  }
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
