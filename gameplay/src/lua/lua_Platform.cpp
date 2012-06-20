#include "Base.h"
#include "ScriptController.h"
#include "Platform.h"
#include "lua_Platform.h"
#include "lua_Global.h"

namespace gameplay
{

void luaRegister_Platform()
{
    ScriptController* sc = ScriptController::getInstance();

    const luaL_Reg lua_members[] = 
    {
        {"enterMessagePump", lua_Platform_enterMessagePump},
        {NULL, NULL}
    };
    const luaL_Reg lua_statics[] = 
    {
        {"create", lua_Platform_static_create},
        {"displayKeyboard", lua_Platform_static_displayKeyboard},
        {"getAbsoluteTime", lua_Platform_static_getAbsoluteTime},
        {"getAccelerometerValues", lua_Platform_static_getAccelerometerValues},
        {"getDisplayHeight", lua_Platform_static_getDisplayHeight},
        {"getDisplayWidth", lua_Platform_static_getDisplayWidth},
        {"isMultiTouch", lua_Platform_static_isMultiTouch},
        {"isVsync", lua_Platform_static_isVsync},
        {"keyEventInternal", lua_Platform_static_keyEventInternal},
        {"setAbsoluteTime", lua_Platform_static_setAbsoluteTime},
        {"setMultiTouch", lua_Platform_static_setMultiTouch},
        {"setVsync", lua_Platform_static_setVsync},
        {"signalShutdown", lua_Platform_static_signalShutdown},
        {"sleep", lua_Platform_static_sleep},
        {"swapBuffers", lua_Platform_static_swapBuffers},
        {"touchEventInternal", lua_Platform_static_touchEventInternal},
        {NULL, NULL}
    };
    std::vector<std::string> scopePath;

    sc->registerClass("Platform", lua_members, NULL, lua_Platform__gc, lua_statics, scopePath);
}

static Platform* getInstance(lua_State* state)
{
    void* userdata = luaL_checkudata(state, 1, "Platform");
    luaL_argcheck(state, userdata != NULL, 1, "'Platform' expected.");
    return (Platform*)((ScriptController::LuaObject*)userdata)->instance;
}

int lua_Platform__gc(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TUSERDATA)
            {
                void* userdata = luaL_checkudata(state, 1, "Platform");
                luaL_argcheck(state, userdata != NULL, 1, "'Platform' expected.");
                ScriptController::LuaObject* object = (ScriptController::LuaObject*)userdata;
                if (object->owns)
                {
                    Platform* instance = (Platform*)object->instance;
                    SAFE_DELETE(instance);
                }
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_enterMessagePump(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TUSERDATA)
            {
                Platform* instance = getInstance(state);
                int result = instance->enterMessagePump();

                // Push the return value onto the stack.
                lua_pushinteger(state, result);

                return 1;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_create(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TUSERDATA)
            {
                // Get parameter 1 off the stack.
                void* userdata1 = ScriptController::getInstance()->getObjectPointer(1, "Game");
                if (!userdata1)
                {
                    lua_pushstring(state, "Failed to retrieve a valid object pointer of type 'Game' for parameter 1.");
                    lua_error(state);
                }
                Game* param1 = (Game*)((ScriptController::LuaObject*)userdata1)->instance;

                ScriptController::LuaObject* object = (ScriptController::LuaObject*)lua_newuserdata(state, sizeof(ScriptController::LuaObject));
                object->instance = (void*)Platform::create(param1);
                object->owns = false;
                luaL_getmetatable(state, "Platform");
                lua_setmetatable(state, -2);

                return 1;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_displayKeyboard(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TBOOLEAN)
            {
                // Get parameter 1 off the stack.
                bool param1 = (luaL_checkint(state, 1) != 0);

                Platform::displayKeyboard(param1);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_getAbsoluteTime(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            long result = Platform::getAbsoluteTime();

            // Push the return value onto the stack.
            lua_pushinteger(state, result);

            return 1;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_getAccelerometerValues(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 2:
        {
            if ((lua_type(state, 1) == LUA_TTABLE || lua_type(state, 1) == LUA_TLIGHTUSERDATA) &&
                (lua_type(state, 2) == LUA_TTABLE || lua_type(state, 2) == LUA_TLIGHTUSERDATA))
            {
                // Get parameter 1 off the stack.
                float* param1 = ScriptController::getInstance()->getFloatPointer(1);

                // Get parameter 2 off the stack.
                float* param2 = ScriptController::getInstance()->getFloatPointer(2);

                Platform::getAccelerometerValues(param1, param2);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 2).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_getDisplayHeight(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            unsigned int result = Platform::getDisplayHeight();

            // Push the return value onto the stack.
            lua_pushunsigned(state, result);

            return 1;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_getDisplayWidth(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            unsigned int result = Platform::getDisplayWidth();

            // Push the return value onto the stack.
            lua_pushunsigned(state, result);

            return 1;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_isMultiTouch(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            bool result = Platform::isMultiTouch();

            // Push the return value onto the stack.
            lua_pushboolean(state, result);

            return 1;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_isVsync(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            bool result = Platform::isVsync();

            // Push the return value onto the stack.
            lua_pushboolean(state, result);

            return 1;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_keyEventInternal(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 2:
        {
            if (lua_type(state, 1) == LUA_TSTRING &&
                lua_type(state, 2) == LUA_TNUMBER)
            {
                // Get parameter 1 off the stack.
                Keyboard::KeyEvent param1 = (Keyboard::KeyEvent)lua_enumFromString_KeyboardKeyEvent(luaL_checkstring(state, 1));

                // Get parameter 2 off the stack.
                int param2 = (int)luaL_checkint(state, 2);

                Platform::keyEventInternal(param1, param2);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 2).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_setAbsoluteTime(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TNUMBER)
            {
                // Get parameter 1 off the stack.
                long param1 = (long)luaL_checklong(state, 1);

                Platform::setAbsoluteTime(param1);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_setMultiTouch(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TBOOLEAN)
            {
                // Get parameter 1 off the stack.
                bool param1 = (luaL_checkint(state, 1) != 0);

                Platform::setMultiTouch(param1);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_setVsync(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TBOOLEAN)
            {
                // Get parameter 1 off the stack.
                bool param1 = (luaL_checkint(state, 1) != 0);

                Platform::setVsync(param1);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_signalShutdown(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            Platform::signalShutdown();
            
            return 0;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_sleep(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if (lua_type(state, 1) == LUA_TNUMBER)
            {
                // Get parameter 1 off the stack.
                long param1 = (long)luaL_checklong(state, 1);

                Platform::sleep(param1);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_swapBuffers(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 0:
        {
            Platform::swapBuffers();
            
            return 0;
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 0).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_Platform_static_touchEventInternal(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 4:
        {
            if (lua_type(state, 1) == LUA_TSTRING &&
                lua_type(state, 2) == LUA_TNUMBER &&
                lua_type(state, 3) == LUA_TNUMBER &&
                lua_type(state, 4) == LUA_TNUMBER)
            {
                // Get parameter 1 off the stack.
                Touch::TouchEvent param1 = (Touch::TouchEvent)lua_enumFromString_TouchTouchEvent(luaL_checkstring(state, 1));

                // Get parameter 2 off the stack.
                int param2 = (int)luaL_checkint(state, 2);

                // Get parameter 3 off the stack.
                int param3 = (int)luaL_checkint(state, 3);

                // Get parameter 4 off the stack.
                unsigned int param4 = (unsigned int)luaL_checkunsigned(state, 4);

                Platform::touchEventInternal(param1, param2, param3, param4);
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 4).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

}
