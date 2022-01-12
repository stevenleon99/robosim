#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "DhParam.hpp"
#include "JointedLink.hpp"
#include "Eigen/Dense"

class Robot {
public:
	Robot(std::string dh_param_filename, Eigen::Vector3f location);
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	// used to update joint angles over some time difference dt
	void					update(float dt);

	// kinematics stuff
	Eigen::Vector3f			getTcpWorldPosition() const;
	Eigen::Vector3f			getTcpWorldPosition(Eigen::VectorXf jointAngles) const;
	Eigen::VectorXf			getTcpSpeed() const;
	Eigen::MatrixXf			getJacobian() const;
	Eigen::MatrixXf			getJacobian(Eigen::VectorXf jointAngles) const;
	Eigen::VectorXf			getJointSpeeds() const;

	// ik targets are always wrt world frame
	Eigen::Vector3f			getTargetTcpPosition() const { return ik_target_; };
	void					setTargetTcpPosition(Eigen::Vector3f new_target_wrt_world);
	Eigen::VectorXf			solveInverseKinematics(Eigen::Vector3f tcp_pos) const;

	// joint angle getters
	Eigen::VectorXf			getJointAngles() const;
	float					getJointAngle(unsigned index) const { return links_[index].getJointRotation(); };
	Eigen::VectorXf			getTargetJointAngles() const;
	float					getTargetJointAngle(unsigned index) const { return links_[index].getJointTargetRotation(); };

	// joint angle setters
	void					setJointTargetAngles(Eigen::VectorXf angles);
	void					setJointTargetAngle(unsigned index, float angle);

	void					renderSkeleton() const;
	std::vector<Vertex>		getMeshVertices() const;

	size_t					getNumJoints() const { return links_.size(); };
	Eigen::Affine3f			getWorldToBase() const { return worldToBase_; };

private:
	Eigen::Affine3f	worldToBase_;

	void					createLinks(const std::vector<DhParam>& params);

	std::vector<JointedLink> links_;
	Eigen::Vector3f ik_target_;
};

