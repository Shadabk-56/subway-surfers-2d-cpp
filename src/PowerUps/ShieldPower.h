#ifndef SHIELDPOWER_H
#define SHIELDPOWER_H

#include "PowerUp.h"

class ShieldPower : public PowerUp {
private:
    sf::Texture shieldTexture; // <--- YE LINE ADD KAREIN
public:
    ShieldPower(int lane, float gameSpeed);
    void activate() override;
    void deactivate() override;
    
};

#endif
