
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/LIB/STD_TYPES.h"

#include "../INCLUDE/MCAL/GI/GI_Interface.h"
#include "../INCLUDE/MCAL/GI/GI_Config.h"
#include "../INCLUDE/MCAL/GI/GI_Private.h"

void GI_VoidSetStatus( u8 Copy_u8Status )
{
    switch ( Copy_u8Status )
    {
        case GI_ON  :    SET_BIT(SREG_REG,7);       break;
        case GI_OFF :    CLR_BIT(SREG_REG,7);       break;
        default  :                                  break;
    }
}

