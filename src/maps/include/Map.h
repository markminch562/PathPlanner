//
// Created by plotb on 8/23/22.
//

#ifndef PATHPLANNER_MAP_H
#define PATHPLANNER_MAP_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <unordered_set>

namespace Mapper
{

    struct Point
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;

    };

    inline bool operator==(const Point& lhs, const Point& rhs)
    {
        return (lhs.R == rhs.R && lhs.B == rhs.B && lhs.G == rhs.G);
    }
    struct Pose
    {
        int x;
        int y;
    };

    inline bool operator==(const Pose& lhs, const Pose& rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    struct GridSize
    {
         int width;
         int height;
    };

    template<typename T>
    class Grid
    {
        GridSize size;
        std::vector<T> GridData;


    public:


        Grid(GridSize _size, std::vector<T> _gridData) : size(_size), GridData(_gridData)
        {

        }
        inline GridSize Size()
        {
            return size;
        }
        inline unsigned int StorageSize()
        {
            return size.width*size.height;
        }
        inline T getData(unsigned int _row, unsigned int _column)
        {
            return GridData[_row*size.width+ _column];
        }
        inline T getData(unsigned int rawLocation)
        {
            return GridData[rawLocation];
        }

        inline T getData(Pose pose)
        {
            return GridData[size.width*pose.y + pose.x];
        }

        inline void setData(unsigned int _row, unsigned int _column, Point data)
        {
            GridData[size.width*_row + _column] = data;
        }
        inline void setData(Pose pose, T Data)
        {
            GridData[size.width*pose.y + pose.x]  = Data;
        }
        [[nodiscard]] inline unsigned int Pose2RawLocation(Pose pose) const
        {
            return size.width*pose.y + pose.x;
        }
        [[nodiscard]] inline Pose RawLocation2Pose(unsigned int RawValue) const
        {
            Pose gridPose{};

            gridPose.y = RawValue/size.width;
            gridPose.x = RawValue %size.width;
            return gridPose;
        }




    };

    class Map_Server
    {
    public:
        std::vector<Point> Grid;
        unsigned int scale;

    };

    class PathPlanner
    {
    protected:
        Pose Start = {0,0};
        Pose Goal = {0,0};
        Grid<Point>* Map;
        //Goal reached conditions
        bool useGoalCondition = true;
        Point GoalCondition;
        Point StartCondition;
    public:
        PathPlanner(Grid<Point>* _map, Point _GoalCondition, Point _StartCondition);
        PathPlanner(Grid<Point>* _map, Pose _Start, Pose _Goal);

        ~PathPlanner();

        inline void Set_Start_End_Pose(Pose _start, Pose  _goal)
        {
            useGoalCondition = false;
            Start = _start;
            Goal = _goal;
        }
        inline void Set_Start_End_Condition(Point _start, Point _goal)
        {
            useGoalCondition = true;
            StartCondition = _start;
            GoalCondition = _goal;
        }

        inline bool isStart(Pose _pose)
        {
            if(useGoalCondition)
            {
                return Map->getData(_pose) == StartCondition;
            }

            return Start ==_pose;

        }

        inline bool isGoal(Pose _pose)
        {

            if(useGoalCondition)
            {
                return Map->getData(_pose) == GoalCondition;
            }

            return Goal ==_pose;


        }


        //MapServer* server = nullptr;

    };


    class DykstraBreadthPlanner : public PathPlanner
    {

        Grid<int> CostMap;
        std::unordered_set<int> SearchedSet;
        std::queue<Pose> SearchQueue;
        bool mPathSearched = false;
        bool mPathFound = false;
        int bestCost = INT64_MAX;
        void UpdateSearched(unsigned int Cost, Pose pose, std::queue<Pose>& nextPass);
    public:
        inline bool PathFound()
        {
            return mPathFound;
        }
        inline bool PathSearched()
        {
            return mPathSearched;
        }
        inline const Grid<int>& getCostMap()
        {
            return CostMap;
        }

        DykstraBreadthPlanner(Grid<Point>* _map, Point _goalCondition, Point _startCondition);
        ~DykstraBreadthPlanner();

        void Update();
        void DrawCostMap();



    };




}




#endif //PATHPLANNER_MAP_H
