namespace ThreeSixty.Smoky.RegionPolygon

open System
open System.Drawing
open System.Drawing.Drawing2D
open System.IO
open System.Reflection
open System.Resources

type RegionPolygon(region: string) as this =

    let rm  = new ResourceManager(this.GetType())
    let mutable oregion: Region = null
    let mutable _minLat:double = 0.0
    let mutable _maxLat:double = 0.0
    let mutable _minLng:double = 0.0
    let mutable _maxLng:double = 0.0
    let scale = 10000.0
    let mutable pointsAll:ResizeArray<float * float> list = []
    let mutable points:ResizeArray<float * float> = null

    let rec processRegionFile (sr: StreamReader) (gp: GraphicsPath list) (px: Single) (py: Single) (start: bool) =
        if sr.EndOfStream then
            gp
        else
            let line = sr.ReadLine()
            if line.Contains("#") then
                processRegionFile sr gp px py start
            else if line.StartsWith("---") || line = "" then
                pointsAll <- new ResizeArray<float * float>()::pointsAll
                processRegionFile sr (new GraphicsPath()::gp) px py start
            else
                let sa = line.ToString().Split(',')
                let x = Convert.ToSingle(Double.Parse(sa.[0]) * scale)
                let y = Convert.ToSingle(Double.Parse(sa.[1]) * scale)
                pointsAll.Item(0).Add(Double.Parse(sa.[0]), Double.Parse(sa.[1]))
                if start then
                    processRegionFile sr gp x y false
                else
                    gp.Item(0).AddLine(px, py, x, y)
                    processRegionFile sr gp x y false

    member this.MinLat = _minLat / scale
    member this.MaxLat = _maxLat / scale
    member this.MinLng = _minLng / scale
    member this.MaxLng = _maxLng / scale
    member this.Points = points

    member public this.ReadRegion() =
        let filename = region + ".txt"
        Console.WriteLine("Loading region: " + region)
        let filename = 
            if File.Exists(filename) then
                region + ".txt"
            else
                @"C:\360\polygon\" + region + ".txt"
        let sr = new StreamReader(filename)
        pointsAll <- [new ResizeArray<float * float>()]
        let gp = processRegionFile sr ([new GraphicsPath()]) (Convert.ToSingle(0.0)) (Convert.ToSingle(0.0)) true

        // Find largest
        let mutable maxSize = Single.MaxValue
        let mutable lst: (int * GraphicsPath * int) list = []
        let mutable i = 0
        for sgp in gp do
            let bbounds = sgp.GetBounds()
            let size2 = Convert.ToInt32(Convert.ToDouble(bbounds.Height +  bbounds.Width) / 100.0)
            let size = sgp.PointCount * size2 
            lst <- (size, sgp, i)::lst
            i <- i + 1

        let size, best, ind = 
            lst
            |> List.sortBy (fun (x, y, i) -> x)
            |> List.rev
            |> List.head
        oregion <- new Region(best)

        // Strip points?
        if pointsAll.Item(ind).Count > 1000 then
            points <- new ResizeArray<float * float>()
            let mutable i = 0
            for p in pointsAll.Item(ind) do
                if i % 4 = 0 then points.Add p
                i <- i + 1
        else
            points <- pointsAll.Item(ind)

        let bounds = best.GetBounds()
        _minLat <- Convert.ToDouble(bounds.Left)
        _maxLat <- Convert.ToDouble(bounds.Right)
        _minLng <- Convert.ToDouble(bounds.Top)
        _maxLng <- Convert.ToDouble(bounds.Bottom)

    member this.InPoly (x: float) (y: float) = oregion.IsVisible(Convert.ToSingle(x * scale), Convert.ToSingle(y * scale))
