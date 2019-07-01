#include <gyroscope.hpp>

namespace r2d2::gyroscope{

    gyroscope::gyroscope_c(base_com & comm) : base_module_c(comm){
        comm.listen_for_frames({r2d2::frame_type::GYROSCOPE});
    }

    void gyroscope_c::process(){
        comm.request(r2d2::frame_type::GYROSCOPE);
        while(comm.has_data()){
            auto frame = comm.get_data();
            // process the frame

            // dont handle the request
            if(frame.request){
                continue;
            }

            const auto data = frame.as_frame_type<frame_type::GYROSCOPE>();
        
            if (data.gyroscope){
                // store the gyroscope struct values in temp values to be later stored in the frame values
                auto temp = get_gyro_xyz();
                gyroscope_frame.x = temp.x;
                gyroscope_frame.y = temp.y;
                gyroscope_frame.z = temp.z;
                break;
            } else if (data.accel){
                // store the acceleration struct values in temp values to be later stored in the frame values
                auto temp = get_accel_xyz();
                gyroscope_accel_frame.x = temp.x;
                gyroscope_accel_frame.y = temp.y;
                gyroscope_accel_frame.z = temp.z;
                break;
            }
        }
    }

}