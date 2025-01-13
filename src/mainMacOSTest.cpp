#include <Unified-Engine/core/instance.h>

#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/Objects/Mesh/Defaults/cube.h>
#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>

#include <Unified-Engine/input/input.h>

#include <Unified-Engine/Objects/scriptObject.h>
#include <Unified-Engine/Core/time.h>


#include <Unified-Engine/Objects/Components/collider.h>
#include <Unified-Engine/Objects/Components/rigidbody.h>

class CameraControl : public UnifiedEngine::ScriptableObject{
public:
    UnifiedEngine::GameObject* OBJ;
    UnifiedEngine::RigidBody* RB;

    glm::vec3 CamRotation = glm::vec3(0.f, 0.f, 0.f);

    bool Space = false;
    bool GToggle = false;
    double GToggleTime = 0.0;

    CameraControl(UnifiedEngine::GameObject* Par, UnifiedEngine::ObjectComponent* Camera, UnifiedEngine::RigidBody* RigidB)
        : UnifiedEngine::ScriptableObject(Par)
    {
        OBJ = Par;
        RB = RigidB;

        OBJ = Par;
        OBJ->Name = "CamCam";

        UnifiedEngine::instantiate(OBJ);

        this->OBJ->Children.push_back(Camera);
        Camera->Parent = OBJ;

        RB->UseGravity = false;
    }

    int Update() {
        // Get the camera directions
        glm::vec3 viewRight = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->GetViewRight();
        glm::vec3 viewFront = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.front();

        // Project `viewRight` and `viewFront` onto the horizontal plane (y = 0)
        viewRight.y = 0.0f;
        viewFront.y = 0.0f;

        // Normalize the vectors to ensure consistent movement speed
        if (glm::length(viewRight) > 0.0f) viewRight = glm::normalize(viewRight);
        if (glm::length(viewFront) > 0.0f) viewFront = glm::normalize(viewFront);

        // Movement input initialization
        glm::vec3 movementInput = glm::vec3(0.0f);

        // Update GToggleTime if Space or GToggle is active
        if (Space || GToggle) {
            GToggleTime += UnifiedEngine::Time.DeltaTime;
        }

        // Reset GToggle and Space after a timeout
        if (GToggleTime > 2) {
            GToggle = false;
            Space = false;
            GToggleTime = 0.0;
        }

        // Movement input calculations
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_W))
            movementInput += viewFront;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_A))
            movementInput -= viewRight;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_S))
            movementInput -= viewFront;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_D))
            movementInput += viewRight;

        // Handle space key logic for gravity toggle
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_SPACE)) {
            movementInput += UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->GetWorldUp();

            if (!Space) {
                // First press of space
                Space = true;
                if (GToggle && GToggleTime < 1) {
                    // Double-tap detected, toggle gravity
                    RB->UseGravity = !RB->UseGravity;
                    // Reset toggling states to avoid multiple toggles within the same double-tap
                    GToggle = false;
                    GToggleTime = 0.0;
                } else {
                    // Start double-tap timer
                    GToggle = true;
                    GToggleTime = 0.0;
                }
            }
        } else {
            // Reset Space when the key is released
            Space = false;
        }

        // Normalize the movement input to avoid faster diagonal movement
        if (glm::length(movementInput) > 0.0f)
            movementInput = glm::normalize(movementInput);

        // Normalize input to ensure consistent movement speed
        if (glm::length(movementInput) > 0.0f)
            movementInput = glm::normalize(movementInput);

        // Apply movement input to the rigid body as acceleration
        RB->Velocity += movementInput * glm::vec3(2.0f, 2.0f, 2.0f); // Adjust multiplier for movement force

        // Player Rotation
        glm::vec2 mPos = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Mouse.GetPosition();
        float yDiff = (CamRotation.x - (mPos.y * 10.f * UnifiedEngine::Time.DeltaTime)) - glm::clamp((CamRotation.x - (mPos.y * 10.f * UnifiedEngine::Time.DeltaTime)), -85.f, 85.f);
        
        // Update pitch, yaw, and roll
        glm::vec3 threeDRotation = glm::vec3(
            -((yDiff) ? 0 : mPos.y) * 10.f * UnifiedEngine::Time.DeltaTime,
            -static_cast<GLfloat>(mPos.x) * 10.f * UnifiedEngine::Time.DeltaTime,
            0.0f
        );
        CamRotation += threeDRotation;
        UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotate(threeDRotation);

        return 0;
    }
};

int main(){
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMajor = 4;
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMinor = 1;

    UnifiedEngine::__INIT__ENGINE();

    // Window Setup
    UnifiedEngine::WindowConfig WinConf = {.x = 1280, .y = 720, .res_x = 1280, .res_y = 720, .title = (char*)"Test Program", .resizable = false, .fullScreen = false, .vsync = false, .fps = 60};
    WinConf.backgroundColor = {0, 0, 0};

    UnifiedEngine::Window GameWindow(WinConf);

    // Skybox
    UnifiedEngine::SkyboxSolidColor box(glm::vec3(135, 206, 235));
    UnifiedEngine::__GAME__GLOBAL__INSTANCE__->skybox = &box;

    //Camera
    UnifiedEngine::Camera Cam;
    UnifiedEngine::instantiate(&Cam);
    
    UnifiedEngine::Shader shader("../rsc/testVertex.glsl", "../rsc/testFragment.glsl");
    UnifiedEngine::ShaderObject shaderObj(&shader);
    UnifiedEngine::ShaderObject shaderObj2(&shader);

    // Create the mesh using the standard cube
    UnifiedEngine::Mesh mesh;
    mesh = UnifiedEngine::Cube();

    UnifiedEngine::BoxCollider Col1(nullptr, UnifiedEngine::computeAABB(&mesh));
    Col1.Offset = glm::vec3(0, 2, 0.5);
    UnifiedEngine::BoxCollider Col2(nullptr, UnifiedEngine::computeAABB(&mesh));

    // Create a game object that is in view
    UnifiedEngine::GameObject gOBJ(mesh, &shaderObj);
    gOBJ.transform.Position.x -= 5;
    gOBJ.transform.SetRotation(glm::vec3(0, 0, 0));
    UnifiedEngine::instantiate(&gOBJ);
    
    UnifiedEngine::GameObject gOBJ2(mesh, &shaderObj2);
    gOBJ2.transform.Position = Col1.Offset;
    gOBJ2.transform.Position.x -= 5;
    gOBJ2.transform.SetRotation(glm::vec3(0, 0, 0));
    UnifiedEngine::instantiate(&gOBJ2);

    UnifiedEngine::InputPointer->Mouse.Cursor.Locked();

    UnifiedEngine::GameObject CamOBJ(UnifiedEngine::Mesh{}, nullptr);
    UnifiedEngine::RigidBody RB(&CamOBJ);
    CameraControl Controller(&CamOBJ, &Cam, &RB);

    // Game loop
    while (!glfwWindowShouldClose(GameWindow.Context()))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Update()){
            FAULT("GAME_INSTANCE::FAILED TO UPDATE!");
            exit(10);
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
        }

        if(UnifiedEngine::InputPointer->Keyboard.KeyPressed(UnifiedEngine::Key_ESCAPE)){
            break;
        }

        LOG(Col1^Col2);

        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Render()){
            FAULT("GAME_INSTANCE::FAILED TO RENDER!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(11);
        }
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return 0;
}
