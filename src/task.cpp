/******************************************************************/
/*  Title:   task.cc                                              */
/*  --------------------------------------------------------------*/
/*  Comment: Implementation of the given task                     */
/*  --------------------------------------------------------------*/
/*  Author:  Jonas M.                                             */
/* ****************************************************************/

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/utility.hpp>

#include <task.hpp>


using namespace cv;

#define WND_NEW_X_POS(FRAME)    rect.x + FRAME
#define WND_NEW_Y_POS(FRAME)    rect.y + FRAME

#define ENDL                    "\n"
#define HELP(err_str)           err_str =  "Usage: task [bm] [sgbm]\n\n"                                    \
                                           "Options:\n"                                                     \
                                           "   bm:   Use \"Block Matching\" to compute a disparity map \n"  \
                                           "   sgbm: Use \"Semi-Global Block Matching\" to compute a disparity amp\n" 

int main(int argc, char **argv)
{
    Mat left_camera_pic, right_camera_pic;
    Mat disp_bm_map, disp_sgbm_map, disp_result;
    Rect rect;
    Ptr<StereoBM> bm;
    Ptr<StereoSGBM> sgbm;
    std::string err_str;
    int open_windows;
    CommandLineParser cp = CommandLineParser(argc, argv,
                                  "{@arg1||}{@arg2||}{help h||}{bm||}{sgbm||}");

    if ((argc != 2 && argc != 3) ||
        (!cp.has("bm") && !cp.has("sgbm"))) {
        HELP(err_str);
        goto error;
    }

    /*
     * Print help
     */
    if (cp.has("help")) {
        HELP(err_str);
        goto error;
    }
        

    left_camera_pic  = imread(TASK_LEFT_FILE_PATH,  IMREAD_GRAYSCALE);
    right_camera_pic = imread(TASK_RIGHT_FILE_PATH, IMREAD_GRAYSCALE);

    if (!(left_camera_pic.data && right_camera_pic.data)) {
        err_str = std::string("Could not read input images\n");
        goto error;
    }

    /*
     * Step 1a: Display left camera picture
     */
    namedWindow(TASK_LT_FRAME_TITLE, WINDOW_AUTOSIZE);
    rect = getWindowImageRect(TASK_LT_FRAME_TITLE);
    moveWindow(TASK_LT_FRAME_TITLE,
                    WND_NEW_X_POS(TASK_LT_PIC_WND_X_OFF),
                    WND_NEW_Y_POS(TASK_LT_PIC_WND_Y_OFF));
    imshow(TASK_LT_FRAME_TITLE, left_camera_pic);
    open_windows++;
    /*
     * Step 1b: Display right camera picture
     */
    namedWindow(TASK_RT_FRAME_TITLE, WINDOW_AUTOSIZE);
    rect = getWindowImageRect(TASK_RT_FRAME_TITLE);
    moveWindow(TASK_RT_FRAME_TITLE,
                    WND_NEW_X_POS(TASK_RT_PIC_WND_X_OFF),
                    WND_NEW_Y_POS(TASK_RT_PIC_WND_Y_OFF));
    imshow(TASK_RT_FRAME_TITLE, right_camera_pic);
    open_windows++;
    /*
     * Step 2a: Compute a disparity map for the left and
     * right picture by using the "Block Matching Algorithm"
     */
    if (cp.has("bm")) {
        /*
         * Compute the Disparity Map.
         */
        bm = StereoBM::create(TASK_BM_MAX_DISP_VAL,TASK_BM_BOX_SIZE);
        bm->compute(left_camera_pic, right_camera_pic, disp_result);
        disp_result.convertTo(disp_bm_map, CV_8U);
        //disp_map *= 8; /* Apply no scaling for now */
        /*
         * Display the Disparity Map in a frame and store the Map
         * in the configured output directory
         */
        namedWindow(TASK_BM_DISP_MAP_FRAME_TITLE, WINDOW_AUTOSIZE);
        rect = getWindowImageRect(TASK_BM_DISP_MAP_FRAME_TITLE);
        moveWindow(TASK_BM_DISP_MAP_FRAME_TITLE,
                        WND_NEW_X_POS(TASK_DISP1_MAP_WND_X_OFF),
                        WND_NEW_Y_POS(TASK_DISP1_MAP_WND_Y_OFF));
        imshow(TASK_BM_DISP_MAP_FRAME_TITLE, disp_bm_map);
        imwrite(TASK_STEREO_BM_FP, disp_bm_map);
        open_windows++;
    }

    /*
     * Step 2b: Compute a disparity map for the left and
     * right picture by using the "Semi Global Bloack
     * Matching Algorithm"
     */
    if (cp.has("sgbm")) {
        /*
         * Compute the Disparity Map with the "Semi Global Matching
         * Algorithm
         */
        sgbm = StereoSGBM::create(TASK_SGBM_MIN_DISP_VAL,
                                  TASK_SGBM_MAX_DISP_VAL,
                                  TASK_SGBM_BOX_SIZE,
                                  TASK_SGBM_WEIGHT_I,
                                  TASK_SGBM_WEIGHT_II);
        sgbm->compute(left_camera_pic, right_camera_pic, disp_result);
        disp_result.convertTo(disp_sgbm_map, CV_8U);
        /*
         * Display and store the Disparity Map
         */
        namedWindow(TASK_SGBM_DISP_MAP_FRAME_TITLE, WINDOW_AUTOSIZE);
        rect = getWindowImageRect(TASK_SGBM_DISP_MAP_FRAME_TITLE);
        if (open_windows == 2) {
            moveWindow(TASK_SGBM_DISP_MAP_FRAME_TITLE,
                            WND_NEW_X_POS(TASK_DISP1_MAP_WND_X_OFF),
                            WND_NEW_Y_POS(TASK_DISP1_MAP_WND_Y_OFF));
        } else {
            moveWindow(TASK_SGBM_DISP_MAP_FRAME_TITLE,
                            WND_NEW_X_POS(TASK_DISP2_MAP_WND_X_OFF),
                            WND_NEW_Y_POS(TASK_DISP2_MAP_WND_Y_OFF));
        }
        imshow(TASK_SGBM_DISP_MAP_FRAME_TITLE, disp_sgbm_map);
        imwrite(TASK_STEREO_SGBM_FP, disp_sgbm_map);
    }

    waitKey();

    return 0;

error:
    std::cout << err_str;
    return 1;
}

