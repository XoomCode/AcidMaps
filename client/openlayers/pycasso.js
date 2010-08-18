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
      type: 'ISOLINE',
      diameter: 64,
      cells: 64
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
     * options - {Ojbect} Hashtable of extra options to tag onto the layer
     */
    initialize: function(name, url, params, options) {
        var newArguments = [];
        //uppercase params
        params = OpenLayers.Util.upperCaseObject(params);
        newArguments.push(name, url, params, options);
        OpenLayers.Layer.Grid.prototype.initialize.apply(this, newArguments);
        OpenLayers.Util.applyDefaults(this.params, 
          OpenLayers.Util.upperCaseObject(this.DEFAULT_PARAMS)
        );
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
          left: bottomLeft.x,
          bottom: bottomLeft.y, 
          right: topRight.x,
          top: topRight.y,
          token: this.token
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
     * transform the given coordinate
     * 
     * Parameters:
     * x - {Number} horizontal position of the point
     * y - {Number} vertical position of the point
     *
     * Returns:
     * {Object} An object with distance to the top left corner in pixels.
     */
    
    pointToPixel: function(x, y) {
      var extent = this.map.maxExtent;
      var dx = x - extent.left;
      var dy = extent.top - y;
      return {x: dx / this.map.resolution, y: dy / this.map.resolution};
    },

    // On token update
    // OpenLayers.Layer.Grid.prototype.mergeNewParams.apply(this, newArguments);
    
    CLASS_NAME: "OpenLayers.Layer.Pycasso"
});
