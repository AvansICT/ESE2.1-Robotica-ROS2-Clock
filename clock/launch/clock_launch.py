from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='seven_segment_display',
            # namespace='seven_segment_display',
            executable='seven_segment_node',
            name='seven_segment_node'
        ),
        Node(
            package='datetime_convertor',
            #namespace='datetime_convertor',
            executable='datetime_convertor_node',
            name='datetime_convertor_node'
        ),
        Node(
            package='datetime_publisher',
            #namespace='datetime_publisher',
            executable='datetime_node',
            name='datetime_node',
            remappings=[
                ('/date_time', '/datetime_input'),
            ]
        )
    ])