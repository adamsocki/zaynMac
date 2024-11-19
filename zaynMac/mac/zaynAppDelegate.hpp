#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include "../render/renderer.hpp"
#include "zayn.hpp"

// Forward declarations
class MyMTKViewDelegate;





class MyMTKViewDelegate : public MTK::ViewDelegate
{
    public:
        MyMTKViewDelegate( MTL::Device* pDevice );
        virtual ~MyMTKViewDelegate() override;
        virtual void drawInMTKView( MTK::View* pView ) override;

    private:
        Renderer* _pRenderer;
};


class ZaynAppDelegate : public NS::ApplicationDelegate
{
public:
    ~ZaynAppDelegate();

    NS::Menu* createMenuBar();

    virtual void applicationWillFinishLaunching(NS::Notification* pNotification) override;
    virtual void applicationDidFinishLaunching(NS::Notification* pNotification) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override;

private:
    NS::Window* _pWindow;
    MTK::View* _pMtkView;
    MTL::Device* _pDevice;
    MyMTKViewDelegate* _pViewDelegate = nullptr;
};
