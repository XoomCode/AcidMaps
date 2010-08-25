/**
 * Class: OpenLayers.Layer.Pycasso
 * Instances of OpenLayers.Layer.Pycasso are used to display data from Pycasso
 *     Web Server.
 * 
 * Inherits from:
 *  - <OpenLayers.Layer.Grid>
 */
OpenLayers.Layer.Pycasso = OpenLayers.Class(OpenLayers.Layer.Grid, {

    /**
     * Constant: DEFAULT_PARAMS
     * {Object} Hashtable of default parameter key/value pairs 
     */
    DEFAULT_PARAMS: {
      TYPE: 'ISOLINE',
      DIAMETER: 64
    },
    
    /**
     * APIProperty: isBaseLayer
     * {Boolean} Pycasso Layer should never be a base layer
     */
    isBaseLayer: false,
    
    
    /**
     * APIProperty: token
     * {String} Used to determine which dataset it's being used
     *          It's updated when the changes the set of points
     */
    token: '',
    
    /**
     * APIProperty: provider
     * {PycassoProvider} The data-source that will be used by this layer
     *                   to generate the maps.
     *                   This object it's constructed on the creation of the 
     *                   layer if you pass a wfs/data parameter.
     *                   It can be changed on runtime without trobules.
     */
    provider: null,
    
    /**
     * Constructor: OpenLayers.Layer.Pycasso
     * Create a new Pycasso layer object
     *
     * Example:
     * (code)
     * var pycasso = new OpenLayers.Layer.Pycasso("Heatmap",
     *                                    "http://pycasso.xoomcode.com/",
     *                                    {type: 'HEATMAP'});
     * (end)
     *
     * Parameters:
     * name - {String} A name for the layer
     * url - {String} Base url for the Pycasso server
     *                (e.g. http://pycasso.xoomcode.com/)
     * params - {Object} An object with key/value pairs representing the
     *                   GetMap query string parameters and parameter values.
     * options - {Object} Hashtable of extra options to tag onto the layer
     */
    initialize: function(name, url, params, options) {
        var newArguments = [];
        
        // Uppercase params
        params = OpenLayers.Util.upperCaseObject(params);
        newArguments.push(name, url, params, options);
        OpenLayers.Layer.Grid.prototype.initialize.apply(this, newArguments);
        OpenLayers.Util.applyDefaults(this.params, 
          OpenLayers.Util.upperCaseObject(this.DEFAULT_PARAMS)
        );
    },
    
    /**
     *
     */
    configure: function(options) {
      if(options && options.wfs){
        if(typeof(options.attribute) == "undefined"){
          alert("Pycasso Layer error\n\rWFS attribute not specified");
          return;
        }
        provider = new Pycasso.Provider.WFS(this, options);
        
      } else if (options && options.points) {
        provider = new Pycasso.Provider.Array(this, options);
      }
    },

    /**
     * Method: destroy
     * Destroy this layer
     */
    destroy: function() {
      // Send DELETE token to the server
      OpenLayers.Layer.Grid.prototype.destroy.apply(this, arguments);  
    },

    
    /**
     * Method: clone
     * Create a clone of this layer
     *
     * Returns:
     * {<OpenLayers.Layer.Pycasso>} An exact clone of this layer
     */
    clone: function (obj) {
        
      if (obj == null) {
          obj = new OpenLayers.Layer.Pycasso(this.name,
            this.url,
            this.params,
            this.getOptions());
      }

      //get all additions from superclasses
      obj = OpenLayers.Layer.Grid.prototype.clone.apply(this, [obj]);

      // copy/set any non-init, non-simple values here

      return obj;
    },    
    
    /**
     * Method: getURL
     * Return a GetMap query string for this layer
     *
     * Parameters:
     * bounds - {<OpenLayers.Bounds>} A bounds representing the bbox for the
     *                                request.
     *
     * Returns:
     * {String} A string with the layer's url and parameters and also the
     *          passed-in bounds and appropriate tile size specified as 
     *          parameters.
     */
    getURL: function (bounds) {
        bounds = this.adjustBounds(bounds);
        var bottomLeft = this.pointToPixel(bounds.left, bounds.bottom);
        var topRight = this.pointToPixel(bounds.right, bounds.top);
        var newParams = {
          LEFT: bottomLeft.x,
          BOTTOM: bottomLeft.y, 
          RIGHT: topRight.x,
          TOP: topRight.y
        };
         
        return this.getFullRequestString(newParams);
    },

    /**
     * Method: addTile
     * addTile creates a tile, initializes it, and adds it to the layer div. 
     *
     * Parameters:
     * bounds - {<OpenLayers.Bounds>}
     * position - {<OpenLayers.Pixel>}
     * 
     * Returns:
     * {<OpenLayers.Tile.Image>} The added OpenLayers.Tile.Image
     */
    addTile: function (bounds,position) {
        return new OpenLayers.Tile.Image(this, position, bounds, 
                                         null, this.tileSize);
    },
    
    /**
     * Method: pointToPixel
     * Transform the given coordinate into a distance in pixels from the top
     * left corner of the map.
     * 
     * Parameters:
     * x - {Number} horizontal position of the point
     * y - {Number} vertical position of the point
     *
     * Returns:
     * {Object} The measured distance to the top left corner in pixels.
     */
    pointToPixel: function(x, y) {
      var extent = this.map.maxExtent;
      var dx = (x - extent.left) / this.map.resolution;
      var dy = (extent.top - y) / this.map.resolution;
      return {x: parseInt(dx) , y: parseInt(dy)};
    },
    
     
    // On token update
    // OpenLayers.Layer.Grid.prototype.mergeNewParams.apply(this, newArguments);
    
    CLASS_NAME: "OpenLayers.Layer.Pycasso"
});

/**
 * Pycasso namespace
 */
Pycasso = {};

/**
 * Pycasso Data providers
 */
Pycasso.Provider = {};

/**
 *
 */
Pycasso.Provider.WFS = OpenLayers.Class({
  initialize: function(layer, source, attribute) {
    alert("wfs provider constructor called");
  }
});

/**
 *
 */
Pycasso.Provider.Array = OpenLayers.Class({

  /**
   * Set of points stored in array format [x,y,v]
   */
  points: [],
  
  projectedPoints: [],

  intervals: [],
  
  cells: 64,
  
  opacity: 1,
  
  initialize: function(layer, options) {
    this.layer = layer;
    this.layer.map.events.register("zoomend", this, this.update);
    this.configure(options);
  },
  
  configure: function(options) {
  	this.points = options.points;
    
    var min = Math.pow(2, 31) - 1;
    var max = -Math.pow(2, 31);
    
    var point;
    for(var i = 0; i < this.points.length; i++){
    	point = this.points[i];
      if(point[2] > max){max = point[2]}
      if(point[2] < min){min = point[2]}
    }
    
    this.intervals = options.intervals || this.generateIntervals(min, max);
    this.cells = options.cells || this.cells;
  },
  
  update: function() {
    this.layer.setOpacity(0);
    this.projectedPoints = [];
    
    var projectedPoint;
    var point;
    for(var i = 0; i < this.points.length; i++){
    	point = this.points[i];
      projectedPoint = this.layer.pointToPixel(point[0], point[1]);
      this.projectedPoints.push(projectedPoint.x + "," + projectedPoint.y + "," + point[2]);
    }
    
    var request = OpenLayers.Request.POST({
      url: this.layer.url,
      data: this.getParameters(),
      headers: {
        "Content-Type": "text/plain"
      },
      scope: this,
      callback: this.handler
    })
  },
  
	getParameters: function(){
		return "INTERVALS=" + this.intervals.join(';') + "&" +
			"POINTS=" + this.projectedPoints.join(';') + "&" + 
			"CELLS=" + this.cells;
	},
  
	generateIntervals: function(min, max){
		var intervals = [];
		increment = parseInt((max - min) / 5);
		intervals.push([min, 0, 0, 0]);
		intervals.push([parseInt(min + increment * 1), 212, 37, 103]);
		intervals.push([parseInt(min + increment * 2), 255, 173, 67]);
		intervals.push([parseInt(min + increment * 3), 224, 240, 123]);
		intervals.push([parseInt(min + increment * 4), 153, 209, 94]);
		intervals.push([max, 47, 171, 165]);
		return intervals;
	},
  
  handler: function(request){
		this.layer.mergeNewParams({TOKEN: request.responseText});
		
		// TODO: Restore old opacity
	  this.layer.setOpacity(1);
  }
});

