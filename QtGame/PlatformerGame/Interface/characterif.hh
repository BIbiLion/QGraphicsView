#ifndef CHARACTERIF_HH
#define CHARACTERIF_HH

#include "Physics/floorcontactbox.hh"

class CharacterIF
{
public:
    CharacterIF() = default;
    virtual ~CharacterIF() = default;

    /*
     * Precondition:
     *
     *
     * Postcondition:
     *
     *
    */
    virtual void accelerateX() = 0;

    virtual void accelerateY() = 0;

    /*
     *
     * Description:
     *  Alters the amount of HP a character has.
     *
    */
    virtual void setHitpoints( int Points ) = 0;

    /*
     *
     * Description:
     *  Returns the amount of HP a character has.
     *
    */
    virtual unsigned int getHitpoints() const = 0;

    /*
     * Description:
     * A function for providing gravity to a character.
     * Used as a function pointer.
     */
    virtual void gravity() = 0;

    virtual void move() = 0;

    ///
    /// \brief addBoxToScene
    ///
    virtual void addBoxToScene() = 0;

private:
    /*
     * A character has the following internal variables:
     * Hitpoints_, MaxHitpoints_, Speed_
     *
    */

};

#endif // CHARACTERIF_HH
