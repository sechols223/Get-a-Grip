extends TouchScreenButton

var current_index = -1

func _process(delta):
	($Label as Label).text = "Index: %d" % current_index

func _input(event):
	if event is InputEventScreenTouch:
		call_deferred("check_press", event)
	if event is InputEventScreenDrag and event.index == current_index:
		global_position = _center_offset(event.position)

func _center_offset(vec: Vector2):
	return vec - texture_normal.get_size() / 2

func check_press(event: InputEventScreenTouch):
	if is_pressed() and event.is_pressed() and current_index == -1:
		current_index = event.index
	elif not event.is_pressed() and current_index == event.index:
		current_index = -1
