# ROS2 Clock

## Make a ROS2 workspace

```bash
cd ~
mkdir ros2_ws
```

## Download code

```bash
mkdir src
cd src
git clone git@github.com:AvansICT/ESE2.1-Robotica-ROS2-Clock.git .
```

## Build

```bash
cd ~/ros2_ws
colcon build
```

## Run

```bash
cd ~/ros2_ws
source install/setup.bash
```

### Date Time Publisher

```bash
ros2 run datetime_publisher datetime_node
```

### Date Time Convertor

```bash
ros2 run datetime_convertor datetime_convertor_node
```

### Seven Sigment Display

```bash
ros2 run seven_segment_display seven_segment_node
```

## Remapping

```text
--ros-args --remap /<topic_old>:=/<topic_new>
```
