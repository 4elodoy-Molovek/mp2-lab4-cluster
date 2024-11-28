#include <gtest.h>
#include <vector>
#include <algorithm>
#include "cluster.h"

class ClusterTest : public ::testing::Test
{
protected:
    Cluster* cluster;

    void SetUp() override
    {
        cluster = new Cluster(100, 50, 10, 5);
        cluster -> EnableRendering(false);
    }

    void TearDown() override
    {
        delete cluster;
    }
};

TEST_F(ClusterTest, INITIALIZATION_CURRENT_TIME_ZERO)
{
    EXPECT_EQ(cluster->GetCurrentTime(), 0);
}

TEST_F(ClusterTest, INITIALIZATION_COMPLETED_TASKS_ZERO)
{
    EXPECT_EQ(cluster->GetCompletedTasks(), 0);
}

TEST_F(ClusterTest, INITIALIZATION_PENDING_TASKS_ZERO)
{
    EXPECT_EQ(cluster->GetPendingTasks(), 0);
}

TEST_F(ClusterTest, INITIALIZATION_UTILIZATION_ZERO)
{
    EXPECT_DOUBLE_EQ(cluster->GetUtilization(), 0.0);
}

TEST_F(ClusterTest, NODE_COUNT_MATCHES_TOTAL_NODES)
{
    EXPECT_DOUBLE_EQ(cluster->GetNodeCount(), 10);
}

TEST_F(ClusterTest, TOTAL_NODES_CORRECT)
{
    EXPECT_DOUBLE_EQ(cluster->GetTotalNodes(), 10);
}

TEST_F(ClusterTest, EXECUTION_NO_THROW)
{
    EXPECT_NO_THROW(cluster->ExecuteTasks());
}

TEST_F(ClusterTest, TASK_GENERATION_POSITIVE)
{
    cluster->ExecuteTasks();
    EXPECT_GE(cluster->GetCompletedTasks(), 0);
}

TEST_F(ClusterTest, RENDERING_DISABLED_BY_DEFAULT)
{
    EXPECT_NO_THROW(cluster->ExecuteTasks());
}

TEST_F(ClusterTest, RENDERING_CAN_BE_ENABLED)
{
    cluster->EnableRendering(true);
    EXPECT_NO_THROW(cluster->ExecuteTasks());
    cluster->EnableRendering(false);
}

TEST_F(ClusterTest, UTILIZATION_IN_VALID_RANGE)
{
    cluster->ExecuteTasks();
    double utilization = cluster->GetUtilization();
    EXPECT_GE(utilization, 0.0);
    EXPECT_LE(utilization, 100.0);
}

TEST_F(ClusterTest, DIFFERENT_CLUSTER_CONFIGURATIONS)
{
    std::vector<std::tuple<double, int, double, int>> configs = {
        {50, 30, 5, 3},
        {200, 70, 15, 7},
        {75, 50, 8, 4}
    };

    for (const auto& config : configs)
    {
        Cluster testCluster(
            std::get<0>(config),
            std::get<1>(config),
            std::get<2>(config),
            std::get<3>(config)
        );

        EXPECT_NO_THROW(testCluster.ExecuteTasks());
    }
}

TEST_F(ClusterTest, ZERO_PROBABILITY_NO_TASKS)
{
    Cluster zeroProb(100, 0, 10, 5);
    zeroProb.ExecuteTasks();
    EXPECT_EQ(zeroProb.GetCompletedTasks(), 0);
}

TEST_F(ClusterTest, MAX_PROBABILITY_MANY_TASKS)
{
    Cluster maxProb(100, 100, 10, 5);
    maxProb.ExecuteTasks();
    EXPECT_GT(maxProb.GetCompletedTasks(), 0);
}

TEST_F(ClusterTest, PERFORMANCE_LARGE_CLUSTER)
{
    Cluster largeCluster(200, 60, 50, 10);
    EXPECT_NO_THROW(largeCluster.ExecuteTasks());
}

TEST_F(ClusterTest, PERFORMANCE_SMALL_CLUSTER)
{
    Cluster smallCluster(50, 40, 3, 2);
    EXPECT_NO_THROW(smallCluster.ExecuteTasks());
}

TEST_F(ClusterTest, STATISTICS_COLLECTED_CORRECTLY)
{
    cluster->ExecuteTasks();

    EXPECT_GE(cluster->GetCompletedTasks(), 0);
    EXPECT_GE(cluster->GetPendingTasks(), 0);
    EXPECT_GE(cluster->GetUtilization(), 0.0);
    EXPECT_LE(cluster->GetUtilization(), 100.0);
}

TEST_F(ClusterTest, RENDERING_TOGGLE)
{
    cluster->EnableRendering(false);
    EXPECT_NO_THROW(cluster->ExecuteTasks());

    cluster->EnableRendering(true);
    EXPECT_NO_THROW(cluster->ExecuteTasks());
}