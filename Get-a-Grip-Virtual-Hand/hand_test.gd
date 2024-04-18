extends Node3D

@onready var hand = $ControllableHand

func _ready():
	hand.set_finger("pinky", 1.0)
	hand.set_finger("ring", 1.0)
	hand.set_finger("index", 1.0)
	hand.set_finger("thumb", 1.0)
