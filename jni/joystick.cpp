#include "joystick.h"
#include "texture.h"

class PushButton : public Texture {
	int texOnPress;
	int texOnRelease;
public:
	enum PBAction{
		PBNone,
		PBPress,
		PBRelease
	};
	PushButton();
	void setTexOnPress(int texID);
	void setTexOnRelease(int texID);
	void draw();
	PBAction pbOnTouch(const TouchAction& touchAct);
private:
	PBAction touch2PBAction(const TouchAction::Action & act);
	PBAction lastAction;
};

PushButton::PushButton() : lastAction(PBNone){
    setUseAlpha(true);
}

void PushButton::setTexOnPress(int texID){
    texOnPress = texID;
}

void PushButton::setTexOnRelease(int texID){
    texOnRelease = texID;
}

void PushButton::draw(){
    if(lastAction == PBPress)
        setID(texOnPress);
    else
        setID(texOnRelease);
    Texture::draw();
}

PushButton::PBAction PushButton::pbOnTouch(const TouchAction& touchAct){
    if(touchAct.act == TouchAction::MOVE || touchAct.act==TouchAction::CANCEL){
        return PBNone;
    }
    lastAction = PBNone;
    Point2f pixel = Screen::pixel2view(Point2i(touchAct.x,touchAct.y));
    if(pixel.x > diagonal.pos0.x && pixel.x < diagonal.pos1.x){
        if(pixel.y < diagonal.pos0.y && pixel.y > diagonal.pos1.y){
            lastAction = touch2PBAction(touchAct.act);
            return lastAction;
        }
    }
    return PBNone;
}

PushButton::PBAction PushButton::touch2PBAction(const TouchAction::Action & act){
    if(act == TouchAction::UP)
        return PBRelease;
    if(act == TouchAction::DOWN)
        return PBPress;
    return PBNone;
}

Joystick::Joystick(){
    pbUp = new PushButton();
    pbDown = new PushButton();
    pbLeft  = new PushButton();
    pbRight = new PushButton();
    pbUp->setDiagonal(Diagonal(-0.15f, 0.4f, 0.15f, 0.0f));
    pbDown->setDiagonal(Diagonal(-0.15f, -0.4f, 0.15f, -0.8f));
    pbLeft->setDiagonal(Diagonal(-0.45f, 0.0f, -0.15f, -0.4f));
    pbRight->setDiagonal(Diagonal(0.15f, 0.0f, 0.45f, -0.4f));
}

Joystick::~Joystick() {
    delete pbUp;
    delete pbDown;
    delete pbLeft;
    delete pbRight;
}

void Joystick::setTex(JoystickAction pbType, int texID, bool onPress){
    PushButton* pb;
    switch(pbType){
        case PBLeft:
            pb = pbLeft;
        break;
        case PBRight:
            pb = pbRight;
        break;
        case PBUp:
            pb = pbUp;
        break;
        case PBDown:
            pb = pbDown;
        break;
        default:return;
    }
    if(onPress)
        pb->setTexOnPress(texID);
    else
        pb->setTexOnRelease(texID);
}

Joystick::JoystickAction Joystick::onTouchEvent(const TouchAction& touchAct){
    if(pbLeft->pbOnTouch(touchAct)==PushButton::PBPress){
        return PBLeft;
    }
    if(pbRight->pbOnTouch(touchAct)==PushButton::PBPress){
        return PBRight;
    }
    if(pbUp->pbOnTouch(touchAct)==PushButton::PBPress){
        return PBUp;
    }
    if(pbDown->pbOnTouch(touchAct)==PushButton::PBPress){
        return PBDown;
    }
    return PBNone;
}

void Joystick::draw(){
    pbUp->draw();
    pbDown->draw();
    pbLeft->draw();
    pbRight->draw();
}
