//
// Created by plotb on 8/23/22.
//

#include "Map.h"
namespace Mapper
{


    PathPlanner::PathPlanner(Grid<Point> *_map, Pose _Start, Pose _Goal) : Map(_map), Start(_Start), Goal(_Goal){
        useGoalCondition = false;
    }

    PathPlanner::PathPlanner(Grid<Point> *_map, Point _GoalCondition, Point _StartCondition) : Map(_map),
                                                                                               StartCondition(_StartCondition), GoalCondition(_GoalCondition){
        useGoalCondition = true;
    }

    PathPlanner::~PathPlanner() = default;

    void DykstraBreadthPlanner::UpdateSearched(unsigned int Cost, Pose pose,  std::queue<Pose> &nextPass) {
        Point Occupied = {0, 0, 0};
        int MovementCost =CostMap.getData(pose);
        //if(SearchedSet.count(Map->Pose2RawLocation(pose)) >0) return;
        //SearchedSet.insert(Map->Pose2RawLocation(pose));
        if(isGoal(pose))
        {
            mPathFound = true;
            if(Cost < bestCost)
            {
                bestCost = Cost;
            }
        }
        if(Map->getData(pose) == Occupied)
        {
            CostMap.setData(pose, 99999);
        }
        else
        {
            if(MovementCost == -1)
            {
                CostMap.setData(pose, Cost);
                nextPass.push(pose);
            }
            else if(MovementCost > Cost)
            {
                CostMap.setData(pose, Cost);
                nextPass.push(pose);
            }
        }


    }

    void DykstraBreadthPlanner::Update()
    {
        if(PathFound())
        {
            return;
        }

        if(SearchQueue.empty()) return;

        std::queue<Pose>NextSearch;
        GridSize gridSize = Map->Size();
        while(!SearchQueue.empty())
        {
            Pose searchValue = SearchQueue.front();
            SearchQueue.pop();
            Pose temp = searchValue;
            unsigned int cost = CostMap.getData(searchValue)+1;
            //check left right, up and down;
            if(searchValue.x -1 >= 0)
            {
                temp = searchValue;
                temp.x--;
                UpdateSearched(cost,temp, NextSearch);
            }
            if(searchValue.x+1 <gridSize.width)
            {
                temp = searchValue;
                temp.x++;
                UpdateSearched(cost,temp, NextSearch);
            }
            if(searchValue.y -1 >= 0)
            {
                temp = searchValue;
                temp.y--;
                UpdateSearched(cost,temp, NextSearch);
            }
            if(searchValue.y +1 < gridSize.height)
            {
                temp = searchValue;
                temp.y++;
                UpdateSearched(cost,temp, NextSearch);
            }


        }
        SearchQueue = NextSearch;

    }

    DykstraBreadthPlanner::DykstraBreadthPlanner(Grid<Point> *_map, Point _goalCondition, Point _startCondition)
            : PathPlanner(_map, _goalCondition, _startCondition), CostMap(_map->Size(), std::vector<int>(_map->StorageSize(), -1)) {

        //Find the Start Position for the searching of the map, if the start is not give to use already then we will have to search for it
        if(useGoalCondition)
        {
            for(int i = 0; i < Map->StorageSize(); i++)
            {

                if(Map->getData(i) == StartCondition)
                {
                    Start = Map->RawLocation2Pose(i);
                }
            }
        }

        //When ever there is not a -1 value inside the data set we know that it has already been reached before, if it has been reached before by a cheaper path then is will not add it to the queue
        CostMap.setData(Start, 0);
        SearchQueue.push(Start);


    }

    void DykstraBreadthPlanner::DrawCostMap() {
        GridSize size = CostMap.Size();
        for(int i = 0; i < 64; i++)
        {
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
        for(int i = CostMap.StorageSize() -1; i >= 0; i--)
        {
            Pose position = CostMap.RawLocation2Pose(i);
            position.x = (CostMap.Size().height -1) - position.x;

            std::cout<<CostMap.getData(position)<<" ";
            if(i%size.width == 0)
            {
                std::cout<<"\n";
            }
        }
        std::cout<<std::endl;

    }

    DykstraBreadthPlanner::~DykstraBreadthPlanner() {

    }


}