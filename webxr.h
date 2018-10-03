#ifndef WEBXR_H_
#define WEBXR_H_

/* Super minimal WebXR device API wrapper */

#ifdef __cplusplus
extern "C"
#endif
{

/** WebXR not supported in this browser */
enum WebXRError {
    WEBXR_ERR_UNSUPPORTED=-2
};

typedef struct WebXRView {
    /* view matrix */
    float viewMatrix[16];
    /* projection matrix */
    float projectionMatrix[16];
    /* x, y, width, height of the eye viewport on target texture */
    int viewport[4];
} WebXRView;

/**
Callback for errors

@param userData User pointer passed to init_webxr()
@param error Error code
*/
typedef void (*webxr_error_callback_func)(void* userData, int error);

/**
Callback for frame rendering

@param userData User pointer passed to init_webxr()
@param time Current frame time
@param modelMatrix Transformation of the XR Device to tracking origin
@param views Array of two @ref WebXRView
*/
typedef void (*webxr_frame_callback_func)(void* userData, int time, float modelMatrix[16], WebXRView views[2]);

/**
Callback for VR session start

@param userData User pointer passed to init_webxr()
*/
typedef void (*webxr_session_start_callback_func)(void* userData);

/**
Callback for VR session end

@param userData User pointer passed to init_webxr()
*/
typedef void (*webxr_session_end_callback_func)(void* userData);

/**
Init WebXR rendering

@param frameCallback Callback called every frame
@param errorCallback Callback called every frame
@param userData User data passed to the callbacks
*/
extern void webxr_init(
        webxr_frame_callback_func frameCallback,
        webxr_session_start_callback_func sessionStartCallback,
        webxr_session_end_callback_func sessionEndCallback,
        webxr_error_callback_func errorCallback,
        void* userData);

/*
Request that the webxr presentation exits VR mode
*/
extern void webxr_request_exit();

/**
Set projection matrix parameters for the webxr session

@param near Distance of near clipping plane
@param far Distance of far clipping plane
*/
extern void webxr_set_projection_params(float near, float far);
}

#endif
