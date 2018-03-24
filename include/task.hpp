/**********************************************************************
 * Title:   task.hpp                                                  *
 * --------------------------------------------------------------------
 * Comment: -                                                         *
 * --------------------------------------------------------------------
 * Author:  Jonas M.                                                  *
 * ********************************************************************/



/***********************************************************************
 * INPUT CONFIGURATION                                                 *
 ***********************************************************************/

/*
 * File name configuration
 * set those macros to the name of the files that should be
 * used to create the disparity map
 * the files should be stored in the pictures/input directory
 */
#define TASK_LEFT_FILE_NAME                  "im0.ppm"       
#define TASK_RIGHT_FILE_NAME                 "im6.ppm"       
#define TASK_STEREO_BM_DISP_MAP              "stereo_bm_disparity.png"
#define TASK_STEREO_SGBM_DISP_MAP            "stereo_sgbm_disparity.png"

/*
 * Input configuration
 */
#define TASK_ROOT_DIR                       "./"
#define TASK_PIC_DIR                        TASK_ROOT_DIR "pictures/"
#define TASK_IN_PIC_DIR                     TASK_PIC_DIR "input/"
#define TASK_LEFT_FILE_PATH                 TASK_IN_PIC_DIR \
                                                TASK_LEFT_FILE_NAME
#define TASK_RIGHT_FILE_PATH                TASK_IN_PIC_DIR \
                                                TASK_RIGHT_FILE_NAME

/*
 * Output configuration
 */
#define TASK_OUT_PIC_DIR                    TASK_PIC_DIR "output/"
#define TASK_STEREO_BM_FP                   TASK_OUT_PIC_DIR TASK_STEREO_BM_DISP_MAP
#define TASK_STEREO_SGBM_FP                 TASK_OUT_PIC_DIR TASK_STEREO_SGBM_DISP_MAP


/***********************************************************************
 * DISPLAY CONFIGURATION                                               *
 ***********************************************************************/
#define TASK_LT_FRAME_TITLE                 "Left Camera Picture"
#define TASK_RT_FRAME_TITLE                 "Right Camera Picture"
#define TASK_BM_DISP_MAP_FRAME_TITLE        "Stereo BM Disparity Map"
#define TASK_SGBM_DISP_MAP_FRAME_TITLE      "Stereo SGBM Disparity Map"

#define TASK_WND_Y_OFF                      -120
#define TASK_WND_X_OFF                      450
#define TASK_LT_PIC_WND_Y_OFF               -TASK_WND_Y_OFF
#define TASK_LT_PIC_WND_X_OFF               -TASK_WND_X_OFF
#define TASK_RT_PIC_WND_Y_OFF               -TASK_WND_Y_OFF
#define TASK_RT_PIC_WND_X_OFF               TASK_WND_X_OFF
#define TASK_DISP1_MAP_WND_X_OFF            3 * TASK_WND_X_OFF
#define TASK_DISP1_MAP_WND_Y_OFF            -TASK_WND_Y_OFF
#define TASK_DISP2_MAP_WND_X_OFF            2 * TASK_WND_X_OFF
#define TASK_DISP2_MAP_WND_Y_OFF            3* (-1 * TASK_WND_Y_OFF)

/***********************************************************************
 * ALGORITHM CONFIGURATION                                             *
 ***********************************************************************/

#define TASK_BM_ID                          "bm"
#define TASK_SGBM_ID                        "sgbm"
/*
 * Stereo BM configuration options
 */
#define TASK_BM_MAX_DISP_VAL                16
#define TASK_BM_BOX_SIZE                    9

/*
 * Stereo SGBM configuration options
 */
#define TASK_SGBM_MIN_DISP_VAL              0
#define TASK_SGBM_MAX_DISP_VAL              16
#define TASK_SGBM_BOX_SIZE                  3
#define TASK_SGBM_WEIGHT_I                  20
#define TASK_SGBM_WEIGHT_II                 30

