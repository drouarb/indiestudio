
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "OgreUI.h"

class TutorialApplication : public OgreUI
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __TutorialApplication_h_
