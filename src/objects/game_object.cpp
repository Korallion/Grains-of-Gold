#import "game_object.h"

bool getIsColliding(GameObject* mover, GameObject* collider) {
    // simple check for external bounds
    if (mover->x + mover->w < collider->x) {
        return false;
    }

    if (mover->x > collider->x + collider->w) {
        return false;
    }

    if (mover->y + mover->h < collider->y) {
        return false;
    }

    if (mover->y > collider->y + collider->h) {
        return false;
    }

    // now we know they are colliding
    return true;
}
