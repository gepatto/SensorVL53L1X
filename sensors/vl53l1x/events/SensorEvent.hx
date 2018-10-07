
package sensors.vl53l1x.events;

import openfl.events.Event;

class SensorEvent extends Event {
    
    public static inline var ERROR       = "vl53l1x_event_error";
    public var description(default, null) : String;

    public function new( type:String,  description:String)
    {
        super(type, true, true);
        this.description = description;
    }


    public override function clone() : Event
    {
		return new SensorEvent( type, this.description );
	}

	public override function toString() : String
    {
       return 'SensorEvent type=$type description=${this.description}';
	}
}