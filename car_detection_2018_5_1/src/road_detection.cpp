// copyright 2018 Yellow One Study
// Created by yellowos on 2018/5/5.
//

#include "../lib/road_detection.h"

int check_cell_mat(const cv::Mat &mat);
void get_road_w_h(float *x_min_max,
                  float *y_min_max,
                  const cv::RotatedRect input_rect);

int road_detection(cv::Mat input_source, int move_step, cv::Mat* output_source, const double &accuracy_phi) {
    const float PI = 3.1415926;
    cv::Mat cell_mat;
    cv::Mat operation_mat;
    cv::resize(input_source, input_source, cv::Size(960, 540));
    cell_mat = cv::Mat::zeros(cv::Size(CELL_SIZE, CELL_SIZE), CV_8UC3);
    cv::Point target_point(0, 0);
    operation_mat = input_source.clone();
    for (; (target_point.y + CELL_SIZE) < input_source.rows; target_point.y += move_step) {
        for (; (target_point.x + CELL_SIZE) < input_source.cols; target_point.x += move_step) {
            input_source(cv::Rect(target_point.x, target_point.y, CELL_SIZE, CELL_SIZE)).copyTo(cell_mat);
            //            cell_mat = input_source(cv::Range(target_point.y, target_point.y + CELL_SIZE),
            //                                    cv::Range(target_point.x, target_point.x + CELL_SIZE));
            int return_value = check_cell_mat(cell_mat);
            if (return_value == ROAD) {
                cv::Point point_list[1][4];
                int npts = 4;
                const cv::Point *ppt[1] = {point_list[0]};
                point_list[0][0] = target_point;
                point_list[0][1] = cv::Point(target_point.x, target_point.y + CELL_SIZE);
                point_list[0][2] = cv::Point(target_point.x + CELL_SIZE, target_point.y + CELL_SIZE);
                point_list[0][3] = cv::Point(target_point.x + CELL_SIZE, target_point.y);
                cv::fillPoly(operation_mat, ppt, &npts, 1, cv::Scalar(255, 255, 255));
            } else if (return_value == NOT_ROAD) {
                cv::Point point_list[1][4];
                int npts = 4;
                const cv::Point *ppt[1] = {point_list[0]};
                point_list[0][0] = target_point;
                point_list[0][1] = cv::Point(target_point.x, target_point.y + CELL_SIZE);
                point_list[0][2] = cv::Point(target_point.x + CELL_SIZE, target_point.y + CELL_SIZE);
                point_list[0][3] = cv::Point(target_point.x + CELL_SIZE, target_point.y);
                cv::fillPoly(operation_mat, ppt, &npts, 1, cv::Scalar(0, 0, 0));
            }
        }
        target_point.x = 0;
    }

    // TODO(yellowos): get the road image
    cv::cvtColor(operation_mat, operation_mat, CV_RGB2GRAY);
    cv::Canny(operation_mat, operation_mat, 128, 128, 3, true);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(operation_mat, contours, hierarchy, CV_RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    std::vector<cv::RotatedRect> rects_temp;
    std::vector<road_part> road_parts;

    printf("new image\n");
    for (auto point_list_ptr = contours.begin(); point_list_ptr != contours.end(); point_list_ptr++) {
        cv::RotatedRect rect;
        rect = cv::minAreaRect(*point_list_ptr);
        cv::Point2f image_points[4];
        rect.points(image_points);

        if ((rect.size.width * rect.size.height) > 900) {
            road_part road_part_temp;
            road_part_temp.rect_road = rect;
            road_part_temp.phi_similarity_sum = 0;
            // road_part_temp.phi_similaritys;
            road_parts.emplace_back(road_part_temp);

            for (int i = 0; i < 4; i++) {
                cv::line(operation_mat, image_points[i], image_points[(i + 1) % 4], cv::Scalar(255));
            }
        }
    }

    for (auto road_part_itr = road_parts.begin(); (road_part_itr + 1) != road_parts.end(); road_part_itr++) {
        decltype(road_part_itr) road_part_itr_2;
        for (road_part_itr_2 = (road_part_itr + 1); road_part_itr_2 != road_parts.end(); road_part_itr_2++) {
            double similarity = 1 - abs(static_cast<double>(road_part_itr->rect_road.angle) - static_cast<double>(road_part_itr_2->rect_road.angle)) / 180.0;
            road_part_itr->phi_similarity_sum += similarity;
            road_part_itr->phi_similaritys.push_back(similarity);
            road_part_itr_2->phi_similarity_sum += similarity;
            road_part_itr_2->phi_similaritys.push_back(similarity);
        }
    }

    cv::RotatedRect road_main_rect;
    std::vector<road_part> main_road_parts;
    {
        double phi = road_parts[0].rect_road.angle;
        double max_similarity = road_parts[0].phi_similarity_sum;
        int64 index;
        for (auto road_part_itr = road_parts.begin(); road_part_itr != road_parts.end(); road_part_itr++) {
            if (road_part_itr->phi_similarity_sum > max_similarity) {
                phi = road_part_itr->rect_road.angle;
                index = road_part_itr - road_parts.begin();
                max_similarity = road_part_itr->phi_similarity_sum;
            }
        }

        road_main_rect.angle = 0;

        for (auto road_part_itr = road_parts.begin(); road_part_itr != road_parts.end(); road_part_itr++) {
            double similarity = 1 - fabs(road_part_itr->rect_road.angle - phi) / 180;
            if (similarity > accuracy_phi) {
                main_road_parts.emplace_back(*road_part_itr);
                cv::RotatedRect rect = road_part_itr->rect_road;
                road_main_rect.angle += static_cast<float>(road_part_itr->rect_road.angle);
                printf("center: %f, %f     size: %f, %f     phi:%f\n", rect.center.x, rect.center.y, rect.size.width,
                       rect.size.height, rect.angle);
            }
        }

        road_main_rect.angle /= main_road_parts.size();
    }

    float x_min_max[2];
    x_min_max[0] = operation_mat.cols;
    x_min_max[1] = 0;
    float y_min_max[2];
    y_min_max[0] = operation_mat.rows;
    y_min_max[1] = 0;

    {
        std::vector<float> y_b;
        std::vector<float> x_b;
        for (auto main_road_part_itr = main_road_parts.begin();
             main_road_part_itr != main_road_parts.end();
             main_road_part_itr++) {
            float y_temp = main_road_part_itr->rect_road.center.y +
                           main_road_part_itr->rect_road.center.x *
                               tan(-1 * main_road_part_itr->rect_road.angle / 180.0 * PI);
            y_b.emplace_back(y_temp -
                             main_road_part_itr->rect_road.size.height / 2 / cos(-1 * main_road_part_itr->rect_road.angle / 180 * PI));
            y_b.emplace_back(y_temp +
                             main_road_part_itr->rect_road.size.height / 2 / cos(-1 * main_road_part_itr->rect_road.angle / 180 * PI));

            float x_temp = main_road_part_itr->rect_road.center.x +
                           main_road_part_itr->rect_road.center.y *
                               tan((main_road_part_itr->rect_road.angle) / 180.0 * PI);
            x_b.emplace_back(x_temp -
                             main_road_part_itr->rect_road.size.width / 2 / cos((-1 * main_road_part_itr->rect_road.angle) / 180 * PI));
            x_b.emplace_back(x_temp +
                             main_road_part_itr->rect_road.size.width / 2 / cos((-1 * main_road_part_itr->rect_road.angle) / 180 * PI));

            //            get_road_w_h(x_min_max, y_min_max, main_road_part_itr->rect_road);
        }

        std::sort(y_b.begin(), y_b.end());
        std::sort(x_b.begin(), x_b.end());

        auto x_b_itr = x_b.begin();
        x_min_max[0] = (*x_b_itr);
        x_b_itr = x_b.end();
        x_b_itr--;
        x_min_max[1] = (*x_b_itr);

        auto y_b_itr = y_b.begin();
        y_min_max[0] = (*y_b_itr);
        y_b_itr = y_b.end();
        y_b_itr--;
        y_min_max[1] = (*y_b_itr);
    }

    {
        float x_temp = (x_min_max[0] + x_min_max[1]) / 2;
        float y_temp = (y_min_max[0] + y_min_max[1]) / 2;
        float y_tan = y_temp / tan(-1 * road_main_rect.angle / 180 * PI);
        float point_x = y_tan - (y_tan - x_temp) * (cos(-2 * road_main_rect.angle / 180 * PI) + 1) / 2;
        float point_y = (y_tan - x_temp) * sin(-2 * road_main_rect.angle / 180 * PI) / 2;
        road_main_rect.center = cv::Point2f(point_x, point_y);
    }

    float dx = x_min_max[1] - x_min_max[0];
    float dy = y_min_max[1] - y_min_max[0];
    double theta = -1 * road_main_rect.angle / 180 * PI;
    road_main_rect.size.width = static_cast<float>(dx * cos(theta));
    road_main_rect.size.height = static_cast<float>(dy * cos(theta));
    /*double theta = road_main_rect.angle/180*PI;
    double m = (1 - (tan(theta)) * (tan(theta))) * cos(theta);
    road_main_rect.size.width = (float)((dx - dy*tan(theta)) / m);
    road_main_rect.size.height = (float)((dy - dx*tan(theta)) / m);*/

    {
        cv::Point2f points[4];
        road_main_rect.points(points);
        printf("finish rect center:%f, %f    size:%f, %f    phi %f",
               road_main_rect.center.x,
               road_main_rect.center.y,
               road_main_rect.size.width,
               road_main_rect.size.height,
               road_main_rect.angle);

        for (int i = 0; i < 4; i++) {
            cv::line(input_source, points[i], points[(i + 1) % 4], cv::Scalar(255));
        }
    }

    //    cv::cvtColor(operation_mat, operation_mat, CV_RGB2GRAY);
    //    cv::threshold(operation_mat, operation_mat, 128, 255, CV_THRESH_BINARY);
    //    cv::medianBlur(operation_mat, operation_mat, CELL_SIZE);
    //    cv::dilate(operation_mat, operation_mat, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(CELL_SIZE*2, CELL_SIZE*2)));

    cv::Mat road_mat;
    {
        road_mat = cv::Mat::zeros(road_main_rect.size, CV_8UC3);
        cv::Point2f img_points[4];
        cv::Point2f warp_points[4];

        warp_points[0] = cv::Point(0, 0);
        warp_points[1] = cv::Point(0, road_mat.rows);
        warp_points[2] = cv::Point(road_mat.cols, 0);
        warp_points[3] = cv::Point(road_mat.cols, road_mat.rows);

        cv::Point2f vec[4];
        road_main_rect.points(vec);

        img_points[1] = vec[0];
        img_points[0] = vec[1];
        img_points[2] = vec[2];
        img_points[3] = vec[3];

        cv::Mat transMat = getPerspectiveTransform(img_points, warp_points);

        warpPerspective(input_source, road_mat, transMat, road_mat.size());
    }
    cv::imshow("source", input_source);
    cv::imshow("road", road_mat);
    //    cv::imshow("image", operation_mat);
    *output_source = road_mat;
    cv::waitKey(10);
    printf("\n\n\n");

    return 0;
}

inline int check_cell_mat(const cv::Mat &mat) {
    cv::Mat avg, stddev;
    cv::meanStdDev(mat, avg, stddev);
    if ((stddev.at<double>(0) < H_STDDEV_MAX) && (stddev.at<double>(1) < S_STDDEV_MAX) && (stddev.at<double>(2) < V_STDDEV_MAX)) {
        if (avg.at<double>(1) > S_AVG_MIN && avg.at<double>(2) > V_AVG_MIN && avg.at<double>(2) < V_AVG_MAX) {
            return ROAD;
        }
    }

    return NOT_ROAD;
}

inline void get_road_w_h(float *x_min_max, float *y_min_max, const cv::RotatedRect input_rect) {
    const int MIN = 0;
    const int MAX = 1;
    cv::Point2f rect_points[4];
    input_rect.points(rect_points);

    for (int i = 0; i < 4; i++) {
        x_min_max[MIN] = (x_min_max[MIN] < rect_points[i].x) ? x_min_max[MIN] : rect_points[i].x;
        x_min_max[MAX] = (x_min_max[MAX] > rect_points[i].x) ? x_min_max[MAX] : rect_points[i].x;
        y_min_max[MIN] = (y_min_max[MIN] < rect_points[i].y) ? y_min_max[MIN] : rect_points[i].y;
        y_min_max[MAX] = (y_min_max[MAX] > rect_points[i].y) ? y_min_max[MAX] : rect_points[i].y;
    }
}
