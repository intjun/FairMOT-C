This is C++ version of [FairMOT](https://github.com/ifzhang/FairMOT) working in Windows, requiring OpenCV and Eigen.

The tracking part has been ported from Python to C++.

The detection and feature extraction parts are still pending. The TensorRT version can refer to [tensorRTIntegrate](https://github.com/dlunion/tensorRTIntegrate).

Currently, the converted TensorRT engine file can successully detect people, but the ReID feature extraction is different from the Python code [issue](https://github.com/dlunion/tensorRTIntegrate/issues/54). Suggestions are welcome. 

## How to Run
1. extract people detection result in [FairMOT](https://github.com/ifzhang/FairMOT) by adding the following code in line 265 in "/src/lib/tracker/multitracker.py"
```
    f = open('tmp_data/%03d.size'%self.frame_id, 'wt')
    f.write('%d %d %d %d'%(dets.shape[0], dets.shape[1], id_feature.shape[0], id_feature.shape[1]))
    f.close()
    dets.tofile('tmp_data/%03d.det'%self.frame_id)
    id_feature.tofile('tmp_data/%03d.feature'%self.frame_id)
```
2. update the "list.txt" in this repository to locate the detection result and feature extraction result

## TODO
add TensorRT for object detection and feature extraction

## Acknowledgement

- Kalman Filter is borrowed from [DeepSort](https://github.com/bitzy/DeepSort), [deep_sort]https://github.com/apennisi/deep_sort
- [FairMOT]（https://github.com/ifzhang/FairMOT）